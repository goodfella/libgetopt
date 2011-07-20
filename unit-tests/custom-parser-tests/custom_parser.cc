#include <iostream>
#include <string>
#include <algorithm>

#include "libgetopt.h"
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

typedef vector<char> arg_cont_t;

bool check_args(const arg_cont_t& args,
		const option<delimited_arg<char>::type_t >& opt)
{
    const arg_cont_t& opt_args = opt.arg().parser().args();

    if( opt_args.size() != args.size() )
    {
	return false;
    }

    if( equal(args.begin(), args.end(), opt_args.begin()) == false )
    {
	return false;
    }

    return true;
}

int main(int argc, char** argv)
{
    option<custom_parser<delimited_arg_parser<char> > > opt1("opt1");
    option<delimited_arg<char>::type_t > opt2("opt2");
    option<delimited_arg<char>::type_t > opt3("opt3");
    option<delimited_arg<char>::type_t > opt4("opt4");

    cmdline_args cargs(argv[0]);
    cmdline_parser parser;

    parser.add_option(&opt1);
    parser.add_option(&opt2);
    parser.add_option(&opt3);
    parser.add_option(&opt4);

    arg_cont_t args;

    for(char i = 0; i < 10; ++i)
    {
	args.push_back(i);
    }

    string opt1_args;
    string opt2_args;
    string opt3_args(1, ',');
    string opt4_args;

    for(arg_cont_t::const_iterator i = args.begin(); i != args.end(); ++i)
    {
	if( opt1_args.empty() == true )
	{
	    opt1_args += (*i + 48);
	}
	else
	{
	    opt1_args += ',';
	    opt1_args += (*i + 48);
	}
    }

    opt2_args += opt1_args + ",";
    opt3_args += opt1_args;
    opt4_args = opt1_args.substr(0, 10) + "," + opt1_args.substr(10);

    cargs.add(&opt1, opt1_args);
    cargs.add(&opt2, opt2_args);
    cargs.add(&opt3, opt3_args);

    parse_result res = parser.parse(cargs.count(), cargs);

    if( res.result() != parse_result::result_success )
    {
	cerr << "parsing failed\n";
	return 1;
    }

    if( check_args(args, opt1) == false )
    {
	cerr << "opt1 args are invalid\n";
	return 1;
    }

    if( check_args(args, opt2) == false )
    {
	cerr << "opt2 args are invalid\n";
	return 1;
    }

    if( check_args(args, opt3) == false )
    {
	cerr << "opt3 args are invalid\n";
	return 1;
    }

    return 0;
}
