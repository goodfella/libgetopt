#include <getopt.h>
#include <unistd.h>
#include <algorithm>
#include <memory>
#include <functional>

#include "cmdline_parser.h"
#include "arg_option.h"
#include "getopt_option.h"
#include "limits.h"

using namespace libgetopt;
using std::string;
using std::vector;
using std::bind2nd;
using std::mem_fun;

const int cmdline_parser::val_adj = libgetopt::limits::max_short_options + 1;

void cmdline_parser::add_option(option_base* opt)
{
    string matching_str;

    option_base* option = find_option(opt, matching_str);

    if( option == NULL )
    {
	m_options.push_back(opt);
    }
    else
    {
	throw duplicate_option(matching_str);
    }
}

void cmdline_parser::add_option(arg_option* arg_opt)
{
    add_option(static_cast<option_base*>(arg_opt));

    // long option without a short option
    if( arg_opt->has_long_option() == true &&
	arg_opt->has_short_option() == false )
    {
	/* change val so that getopt returns a unique value
	 * for the option
	 */
	arg_opt->set_val(m_arg_options.size() + cmdline_parser::val_adj);
    }

    m_arg_options.push_back(arg_opt);
}

option_base* cmdline_parser::find_option(option_base* opt, string& matching_str)
{
    option_list_t::const_iterator option = m_options.end();

    if( opt->has_long_option() )
    {
	option = find_if(m_options.begin(), m_options.end(),
			 bind2nd(mem_fun(option_base::long_opt_pred),
				 opt->long_option().c_str()));

	if( option != m_options.end() )
	{
	    matching_str = opt->long_option();
	    return *option;
	}
    }

    if( opt->has_short_option() )
    {
	option = find_if(m_options.begin(), m_options.end(),
			 bind2nd(mem_fun(option_base::short_opt_pred),
				 opt->short_option()));

	if( option != m_options.end() )
	{
	    matching_str = "";
	    matching_str += opt->short_option();
	    return *option;
	}
    }

    return NULL;
}

cmdline_parser::parse_result cmdline_parser::parse(int argc, char* const argv[])
{
    vector< ::option> longopts;

    ::option last_opt = {0,0,0,0};

    string optstring;

    // generate the longopts and optstring
    for(option_list_t::const_iterator i = m_options.begin();
	i != m_options.end();
	++i)
    {
	getopt_option gopt(*i);

	if( (*i)->has_long_option() == true )
	{
	    ::option opt = gopt.option();

	    longopts.push_back(opt);
	}

	if( (*i)->has_short_option() == true )
	{
	    optstring += gopt.optstring();
	}
    }

    longopts.push_back(last_opt);


    // parse command line
    while ( true )
    {
	int opt;
	int opt_index = -1;

	opt = getopt_long(argc, argv, optstring.c_str(), &longopts[0], &opt_index);

	// finished parsing args
	if( opt == -1 )
	{
	    break;
	}
	// ignore flags
	else if( opt == 0 )
	{
	    continue;
	}
	// invalid option or missing argument
	else if( opt == '?' || opt == ':')
	{
	    // invalid option given
	    if( optopt == 0 )
	    {
		return parse_result(parse_result::result_invalid_option);
	    }

	    // option is missing an argument
	    else
	    {
		arg_option_list_t::iterator option = m_arg_options.end();

		option = find_if(m_arg_options.begin(),
				 m_arg_options.end(),
				 bind2nd(mem_fun(option_base::val_pred),
					 optopt));

		assert(option != m_arg_options.end());

		arg_option* arg_opt = *option;

		return parse_result(arg_opt, parse_result::result_missing_arg);
	    }
	}

	arg_option_list_t::iterator option = m_arg_options.end();

	option = find_if(m_arg_options.begin(),
			 m_arg_options.end(),
			 bind2nd(mem_fun(option_base::val_pred), opt));


	assert( option != m_arg_options.end() );

	arg_option* arg_opt = *option;

	if( arg_opt->set(optarg) == false )
	{
	    return parse_result(arg_opt, parse_result::result_invalid_arg, optarg);
	}
    }

    return parse_result();
}
