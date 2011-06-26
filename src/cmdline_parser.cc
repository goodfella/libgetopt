#include <getopt.h>
#include <unistd.h>
#include <algorithm>
#include <memory>
#include <functional>
#include <string>
#include <cassert>

#include <iostream>

using namespace std;

#include "cmdline_parser.h"
#include "option_list.h"

using namespace libgetopt;
using std::string;
using std::vector;
using std::bind2nd;

bool cmdline_parser::is_in_use = false;


option_base const * const cmdline_parser::find_option(option_base const * const opt,
						      const option_list_t& options)
{
    option_list_t::const_iterator opt_map =
	find(options.begin(), options.end(), opt);

    if( opt_map != options.end() )
    {
	return opt_map->option;
    }

    return NULL;
}


void cmdline_parser::add_option(option_base* opt)
{
    option_base const * const option = find_option(opt, m_options);

    if( option == NULL )
    {
	m_options.push_back(option_map(opt));
    }
    else
    {
	throw duplicate_option(opt->name.string_name());
    }
}

parse_result cmdline_parser::parse(int argc, char* const argv[])
{
    if( is_in_use == true )
    {
	throw parser_in_use();
    }

    option_list longopts(m_options.size() + 1);

    ::option last_opt = {0,0,0,0};

    // we want getopt_long to return ':' when it encounters a missing argument
    string optstring = ":";

    // generate the longopts and optstring
    for(option_list_t::iterator i = m_options.begin();
	i != m_options.end(); ++i)
    {
	int val = 0;

	option_base const * const opt = i->option;

	if( opt->name.has_long_name() == true )
	{
	    val = longopts.add_option(opt);
	}

	if( opt->name.has_short_name() == true )
	{
	    if( val != 0 )
	    {
		assert(val == opt->name.short_name());
	    }

	    val = opt->name.short_name();
	    optstring += opt->name.short_name();
	    optstring += opt->arg_required() == true ? ":" : "::";
	}

	i->val = val;
    }

    longopts.add_option(last_opt);

    int opt = -1;
    int opt_index = -1;
    is_in_use = true;

    // parse command line
    while ( (opt = getopt_long(argc, argv, optstring.c_str(), longopts, &opt_index)) != -1 )
    {
	switch (opt)
	{
	    // flag, no need to do anything
	    case 0:
	    {
		continue;
	    }

	    // invalid option
	    case '?':
	    {
		string invalid_opt = argv[optind];
		return parse_result(invalid_opt);
	    }

	    // missing argument
	    case ':':
	    {
		option_list_t::const_iterator opt_map = m_options.end();

		opt_map = find(m_options.begin(), m_options.end(), opt);

		assert( opt_map != m_options.end() );

		option_base* error_opt = opt_map->option;
		return parse_result(error_opt);
	    }

	    // option found
	    default:
	    {
		option_list_t::iterator opt_map = m_options.end();

		opt_map = find(m_options.begin(), m_options.end(), opt);

		// by definition an option should be found
		assert( opt_map != m_options.end() );

		option_base* option = opt_map->option;

		// optarg should be set if an arg is required
		assert( option->arg_required() == false ||
			option->arg_required() == true && optarg != NULL );

		string error_str;

		if( option->arg_required() == true ||
		    option->arg_required() == false && optarg != NULL )
		{
		    if( option->parse_arg(optarg, &error_str) == false )
		    {
			return parse_result(option, optarg, error_str);
		    }
		}
		else
		{
		    option->set_present(true);
		}
	    }
	}

	opt = -1;
	opt_index = -1;
    }

    return parse_result();
}
