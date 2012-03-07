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

bool lexer_exception(int argc, char ** argv, cmdline_lexer& lexer)
{
    try
    {
	lexer.reset(argc, argv);
    }
    catch(logic_error& ex)
    {
	return true;
    }
    catch(...)
    {
	return false;
    }

    return false;
}

int main(int argc, char ** argv)
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
	cerr << "test_lexer failed with unnamed parameter\n";
	return 1;
    }

    lexer.reset();

    if( test_lexer(lexer) == false )
    {
	cerr << "test_lexer failed after first reset]n";
	return 1;
    }

    if( lexer_exception(-1, NULL, lexer) == false )
    {
	cerr << "no exception with -1 argc, and NULL argv\n";
	return 1;
    }

    if( lexer_exception(-1, argv, lexer) == false )
    {
	cerr << "no exception with -1 argc, and valid argv\n";
	return 1;
    }

    if( lexer_exception(0, NULL, lexer) == true )
    {
	cerr << "exception with 0 argc, and NULL argv\n";
	return 1;
    }

    if( lexer_exception(argc, NULL, lexer) == false )
    {
	cerr << "no exception with argc and NULL argv\n";
	return 1;
    }

    if( lexer_exception(argc, argv, lexer) == true )
    {
	cerr << "exception with good argv and argv";
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
