#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdlib>

#include "libunit-test.h"
#include "cmdline_lexer.h"
#include "cmdline_token.h"
#include "set.h"

using namespace std;
using namespace libgetopt::unit_tests;
using namespace libgetopt;

struct test_case
{
	test_case(const string& opt_name, const string& opt_arg, int test_id):
		name(opt_name),
		arg(opt_arg),
		id(test_id)
		{}

	string name;
	string arg;
	int id;
};

bool operator < (const test_case& lhs, const test_case& rhs)
{
	return lhs.id < rhs.id;
}

ostream& operator << (ostream& out, const test_case& test)
{
	out << "name = " << test.name << " : " << "arg = " << test.arg;
	return out;
}

typedef set<test_case> test_set_t;

void fail(const stringstream& message, const test_case& test, const cmdline_token& token)
{
	cerr << "test: " << test << endl;
	cerr << "token.parameter = " << token.parameter() << endl;
	cerr << "token.name = " << token.name() << endl;
	cerr << "token.arg = " << token.arg() << endl;
	cerr << "token.type = " << token.type() << endl;
	cerr << "cmdline_lexer_full_test failed: " << message.str() << endl;
	exit(1);
}

void run_test(const test_set_t& tests)
{
	cmdline_args args;
	string arg_string = "";

	for(test_set_t::const_iterator test = tests.begin(); test != tests.end(); ++test)
	{
		if( test->name.size() > 1 )
		{
			args.add("--" + test->name + '=' + test->arg);
		}
		else if( test->name.size() == 1 )
		{
			args.add('-' + test->name + test->arg);
		}
		else
		{
			args.add(test->arg);
		}
	}

	test_set_t::const_iterator test = tests.begin();
	cmdline_lexer lexer(args.count(), args);
	cmdline_token token;

	while( lexer.next_parameter(&token) == true )
	{
	        if( token.name() != test->name )
		{
			fail(stringstream("token name does not match test name"), *test, token);
		}

	        if( token.name().size() > 0 && token.arg() != test->arg )
	        {
			fail(stringstream("token arg does not match test arg"), *test, token);
		}

		if( test->name.size() > 1 && token.type() != cmdline_token::long_named )
		{
			fail(stringstream("token type missmatch expected: long_named"), *test, token);
		}
		else if( test->name.size() == 1 && token.type() != cmdline_token::short_named )
		{
			fail(stringstream("token type missmatch expected: short_named"), *test, token);
		}
		else if( test->name.size() == 0 && token.type() != cmdline_token::unnamed )
		{
			fail(stringstream("token type missmatch expected: unnamed"), *test, token);
		}

		++test;
	}

	if( test != tests.end() )
	{
		fail(stringstream("all tests were not ran"), *test, token);
	}
}

test_case long_name("name", "", 1);
test_case short_name("n", "", 2);
test_case long_name_arg("name", "arg", 3);
test_case short_name_arg("n", "arg", 4);
test_case unnamed_param("", "arg", 5);

int main()
{
	test_set_t test_cases;

	test_cases.add_element(long_name);
	test_cases.add_element(short_name);
	test_cases.add_element(long_name_arg);
	test_cases.add_element(short_name_arg);
	test_cases.add_element(unnamed_param);

	test_set_t::powerset_t tests = test_set_t::powerset(test_cases);

	for(test_set_t::powerset_iterator subtest = tests.begin();
	    subtest != tests.end();
	    ++subtest)
	{
		do
		{
			run_test(*subtest);
			
		} while ( next_permutation(subtest->begin(), subtest->end()) == true );
	}

	return 0;
}
