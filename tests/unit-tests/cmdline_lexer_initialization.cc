#include <iostream>
#include <string>

#include "libunit-test.h"
#include "cmdline_lexer.h"
#include "cmdline_token.h"

using namespace std;
using namespace libgetopt::unit_tests;
using namespace libgetopt;

bool test_lexer(cmdline_lexer& lexer)
{
    cmdline_token token;

    bool result = lexer.next_parameter(&token);
    if( result == false )
    {
	cerr << "lexer.next_parameter returned false\n";
	return false;
    }

    result = lexer.next_parameter(&token);
    if( result == true )
    {
	cerr << "lexer.next_parameter returned true after parsing finished\n";
	return false;
    }

    return true;
}

int main()
{
    cmdline_lexer lexer;
    cmdline_token token;

    if( lexer.next_parameter(&token) == true )
    {
	cerr << "lexer.next_parameter returned true with an empty lexer\n";
	return 1;
    }

    cmdline_args args("abc");
    lexer.reset(args.count(), args);

    if( test_lexer(lexer) == false )
    {
	return 1;
    }

    lexer.reset();

    if( test_lexer(lexer) == false )
    {
	return 1;
    }

    try
    {
	    lexer.reset(0, NULL);
    }
    catch(logic_error& ex)
    {}
    catch(...)
    {
	    return 1;
    }

    args.clear();
    lexer.reset(args.count(), args);

    if( lexer.next_parameter(&token) == true )
    {
	cerr << "lexer.next_parameter returned true with empty args\n";
	return 1;
    }

    return 0;
}
