#include <getopt.h>
#include <unistd.h>
#include <algorithm>
#include <memory>
#include <functional>

#include "cmdline_parser.h"
#include "arg_option.h"
#include "getopt_option.h"

using namespace libgetopt;
using std::string;
using std::vector;
using std::bind2nd;
using std::mem_fun;

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


    // process flags
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
	else if( opt == '?' || opt == ':')
	{
	    // invalid option given
	    if( optopt == 0 )
	    {
		return parse_result(NULL, parse_result::result_invalid_option);
	    }

	    // option is missing an argument
	    else
	    {
		arg_option_list_t::iterator option = m_arg_options.end();

		option = find_if(m_arg_options.begin(),
				 m_arg_options.end(),
				 bind2nd(mem_fun(option_base::val_pred),
					 optopt));

		arg_option* arg_opt = NULL;

		if( option != m_arg_options.end() )
		{
		    arg_opt = *option;
		}

		return parse_result(arg_opt, parse_result::result_missing_arg);
	    }
	}

	// zero was returned, but no long option was found
	assert( (opt != 0 || opt_index != -1) );

	arg_option_list_t::iterator option = m_arg_options.end();

	// long option found
	if( opt == 0 && optind != -1 )
	{
	    option = find_if(m_arg_options.begin(),
			     m_arg_options.end(),
			     bind2nd(mem_fun(option_base::long_opt_pred),
				     longopts[optind].name));
	}
	// short option found
	else if( opt != 0 )
	{
	    option = find_if(m_arg_options.begin(),
			     m_arg_options.end(),
			     bind2nd(mem_fun(option_base::val_pred),
				     opt));
	}

	// no arg_option found, just a flag
	if( option == m_arg_options.end() )
	{
	    continue;
	}

	arg_option* arg_opt = *option;

	if( arg_opt->set(optarg) == false )
	{
	    return parse_result(arg_opt, parse_result::result_invalid_arg);
	}
    }

    return parse_result();
}
