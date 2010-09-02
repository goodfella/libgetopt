#include <getopt.h>
#include <unistd.h>
#include <algorithm>
#include <memory>
#include <functional>

#include <iostream>

#include "cmdline_parser.h"
#include "arg_option_base.h"
#include "getopt_option.h"

using namespace libgetopt;
using std::string;
using std::vector;
using std::bind2nd;
using std::mem_fun;

using namespace std;

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

    while ( true )
    {
	int opt;
	int optind = 0;

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
	// ignore flag returns
	else if( opt == 0 )
	{
	    continue;
	}

	// find the matching option
	vector<arg_option_base*>::iterator iter = m_arg_options.end();

	iter = find_if(m_arg_options.begin(),
		       m_arg_options.end(),
		       bind2nd(mem_fun(&arg_option_base::matches),opt));

	// there is a problem here
	if( iter == m_arg_options.end() )
	{
	    break;
	}

	arg_option_base* arg_opt = *iter;

	arg_opt->set(optarg);
    }
}
