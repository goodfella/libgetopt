#include <iostream>
#include <string>

#include "libunit-test.h"
#include "cmdline_lexer.h"
#include "cmdline_token.h"

using namespace std;
using namespace libgetopt::unit_tests;
using namespace libgetopt;

bool check_parser(cmdline_lexer& lexer,
		  const string& parameter,
		  const string& name,
		  const string& arg)
{
    cmdline_token token;

    if( lexer.next_parameter(&token) == false )
    {
	cerr << "next_parameter returned false\n";
	return false;
    }

    if( token.parameter != parameter )
    {
	cerr << "token.parameter != " << parameter << endl;
	return false;
    }

    if( token.name != name )
    {
	cerr << "token.name != " << name << endl;
	return false;
    }

    if( token.arg != arg )
    {
	cerr << "token.arg != " << arg << endl;;
	return false;
    }

    if( token.type != cmdline_token::long_named )
    {
	cerr << "token.type != long_named\n";
	return false;
    }

    return true;
}

bool test_name(const string& name)
{
    string parameter = "--" + name;
    cmdline_args args(parameter);

    cmdline_lexer lexer(args.count(), args);

    if( check_parser(lexer, parameter, name, "") == false )
    {
	return false;
    }


    args.clear();
    parameter += "=";
    args.add(parameter);
    lexer.reset(args.count(), args);

    if( check_parser(lexer, parameter, name, "") == false )
    {
	return false;
    }


    args.clear();
    parameter += "abc";
    args.add(parameter);
    lexer.reset(args.count(), args);

    if( check_parser(lexer, parameter, name, "abc") == false )
    {
	return false;
    }

    return true;
}

int main()
{
    if( test_name("-") == false )
    {
	return 1;
    }

    if( test_name("l") == false )
    {
	return 1;
    }

    if( test_name("=") == false )
    {
	return 1;
    }

    if( test_name("long") == false )
    {
	return 1;
    }

    return 0;
}
