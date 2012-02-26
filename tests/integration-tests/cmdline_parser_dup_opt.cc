#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

#include "libgetopt.h"
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

struct test_failed: logic_error
{
	test_failed(): logic_error("test failed") {}
};

void run_test(cmdline_parser& parser, option_base* opt)
{
    try
    {
	parser.add_option(opt);
    }
    catch(duplicate_option& ex)
    {
	return;
    }

    cerr << "duplicate_option exception not thrown\n";
    throw test_failed();
}

int main()
{
    option<string> opt1("string",'s');
    option<string> opt2("string");
    option<string> opt3('s');

    vector<option_base*> options;

    options.push_back(&opt1);
    options.push_back(&opt2);
    options.push_back(&opt3);

    cmdline_parser parser;
    parser.add_option(&opt1);

    for( vector<option_base*>::iterator i = options.begin();
	 i != options.end();
	 ++i)
    {
	try
	{
	    run_test(parser, *i);
	}
	catch(test_failed& ex)
	{
	    return 1;
	}
	catch(...)
	{
	    cerr << "unknown error\n";
	    throw;
	}
    }
}
