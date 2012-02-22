#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

#include "libunit-test.h"
#include "cmdline_lexer.h"

using namespace std;
using namespace libgetopt::unit_tests;
using namespace libgetopt;


struct test_failed: public logic_error
{
	test_failed(const string& msg): logic_error(msg) {}
};


void test_lexer_constructor(int argc, char** argv)
{
    stringstream ss;

    try
    {
	cmdline_lexer lexer(argc, argv);
    }
    catch(logic_error& ex)
    {
	return;
    }

    ss << "no exception thrown for argc: " << argc << " argv: " << argv;
    throw test_failed(ss.str());
}

void test_lexer_reset(int argc, char** argv)
{
    stringstream ss;

    cmdline_lexer lexer;

    try
    {
	lexer.reset(argc, argv);
    }
    catch(logic_error& ex)
    {
	return;
    }

    ss << "no exception thrown for argc: " << argc << " argv: " << argv;
    throw test_failed(ss.str());
}


typedef vector<pair<int, char**> > test_list_t;


int main(int argc, char** argv)
{
    test_list_t tests;

    char const * bad_argv[] = {"bad-argv", "bad-argv"};

    tests.push_back(make_pair(0, argv));
    tests.push_back(make_pair(1, static_cast<char**>(NULL)));
    tests.push_back(make_pair(1, const_cast<char**>(bad_argv)));

    for(test_list_t::const_iterator i = tests.begin();
	i != tests.end();
	++i)
    {
	try
	{
	    test_lexer_constructor(i->first, i->second);
	    test_lexer_reset(i->first, i->second);
	}
	catch(test_failed& ex)
	{
	    cerr << "test failed: " << ex.what() << endl;
	    return 1;
	}
	catch(...)
	{
	    throw;
	}
    }

    return 0;
}
