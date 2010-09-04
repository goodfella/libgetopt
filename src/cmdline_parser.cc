#include <getopt.h>
#include <unistd.h>
#include <algorithm>
#include <memory>
#include <functional>

#include "cmdline_parser.h"
#include "arg_option_base.h"
#include "getopt_option.h"

using namespace libgetopt;
using std::string;
using std::vector;
using std::bind2nd;
using std::mem_fun;

void cmdline_parser::parse(int argc, char* const argv[])
{
    vector< ::option> longopts;

    ::option last_opt = {0,0,0,0};

    string optstring;

    // generate the longopts and optstring
    for(vector<option_base*>::const_iterator i = m_options.begin();
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
	int optind = -1;

	opt = getopt_long(argc, argv, optstring.c_str(), &longopts[0], &optind);

	// finished parsing args
	if( opt == -1 )
	{
	    break;
	}
	else if( opt == '?' )
	{
	    break;
	}

	// find the matching option
	vector<arg_option_base*>::iterator option = m_arg_options.end();

	option = find_if(m_arg_options.begin(),
			 m_arg_options.end(),
			 bind2nd(mem_fun(&arg_option_base::matches),opt));

	/* by definition an arg option must be found because
	 * getopt_long returned a value other than -1, '?', or 0
	 */
	assert(option != m_arg_options.end());

	arg_option_base* arg_opt = *option;

	arg_opt->set(optarg);
    }
}
