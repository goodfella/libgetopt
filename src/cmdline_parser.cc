#include <getopt.h>
#include <unistd.h>
#include <algorithm>
#include <memory>
#include <functional>
#include <string>

#include "cmdline_parser.h"
#include "arg_option.h"
#include "getopt_option.h"
#include "limits.h"

using namespace libgetopt;
using std::string;
using std::vector;
using std::bind2nd;
using std::mem_fun;


void cmdline_parser::add_option(option_base* opt)
{
    option_base* option = find_option(opt, m_options);

    if( option == NULL )
    {
	m_options.push_back(opt);
    }
    else
    {
	throw duplicate_option(opt->name());
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
	arg_opt->set_val(m_arg_options.size() + limits::max_short_options + 1);
    }

    m_arg_options.push_back(arg_opt);
}

cmdline_parser::parse_result cmdline_parser::parse(int argc, char* const argv[]) const
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


    int opt = -1;
    int opt_index = -1;

    // parse command line
    while ( (opt = getopt_long(argc, argv, optstring.c_str(), &longopts[0], &opt_index)) != -1 )
    {
	switch (opt)
	{
	    // flag, no need to do anything
	    case 0:
	    {
		continue;
	    }

	    // invalid option or missing argument
	    case '?':
	    case ':':
	    {
		arg_option_list_t::const_iterator option = m_arg_options.end();

		option = find_if(m_arg_options.begin(),
				 m_arg_options.end(),
				 bind2nd(mem_fun(option_base::val_pred),
					 optopt));

		// invalid option
		if( option == m_arg_options.end() )
		{
		    string invalid_opt;
		    invalid_opt += static_cast<char>(optopt);

		    return parse_result(invalid_opt);
		}

		// missing argument
		else
		{
		    arg_option* arg_opt = *option;
		    return parse_result(arg_opt);
		}
	    }

	    // option found
	    default:
	    {
		arg_option_list_t::const_iterator option = m_arg_options.end();

		option = find_if(m_arg_options.begin(),
				 m_arg_options.end(),
				 bind2nd(mem_fun(option_base::val_pred), opt));

		// by definition an option should be found
		assert( option != m_arg_options.end() );

		arg_option* arg_opt = *option;

		assert( (arg_opt->arg_policy() == arg_policy_optional)
			|| (optarg != NULL) );

		string error_str;

		if( arg_opt->set(optarg, error_str) == false )
		{
		    return parse_result(arg_opt, optarg, error_str);
		}
	    }
	}
    }

    return parse_result();
}
