#include <iostream>
#include <string>

#include "libunit-test.h"
#include "cmdline_lexer.h"
#include "cmdline_token.h"

using namespace std;
using namespace libgetopt::unit_tests;
using namespace libgetopt;

bool test_short_name(const string& name, const string& arg)
{
    string parameter = "-" + name + arg;
    cmdline_args args(parameter);

    cmdline_lexer lexer(args.count(), args);
    cmdline_token token;

    if( lexer.next_parameter(&token) == false )
    {
	cerr << "lexer.next_parameter returned false with: " << parameter << endl;
	return false;
    }

    if( token.name != name )
    {
	cerr << "token.name missmatch for: " << parameter << endl;
	return false;
    }

    if( token.arg != arg )
    {
	cerr << "token.arg missmatch for: " << parameter << endl;
	return false;
    }

    if( token.type != cmdline_token::short_named )
    {
	cerr << "token.type missmatch for: " << parameter << endl;
	return false;
    }

    return true;
}

int main()
{
    if( test_short_name("s", "") == false )
    {
	return 1;
    }

    if( test_short_name("s", "abc") == false )
    {
	return 1;
    }

    return 0;
}
