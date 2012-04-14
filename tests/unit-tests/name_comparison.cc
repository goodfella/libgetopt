#include <iostream>
#include <functional>
#include <vector>
#include <utility>
#include <stdexcept>
#include <string>
#include <sstream>

#include "libgetopt.h"
#include "libunit-test.h"

using namespace libgetopt;
using namespace libgetopt::unit_tests;
using namespace std;

/*
 * 0 no long name
 * 1 one long name
 * 2 long names equal
 * 3 long names not equal
 *
 * A no short name
 * B one short name
 * C short names equal
 * D short names not equal
 *
 * Combinations:
 *
 * 0 A invalid because both parameter names are invalid
 * 0 B invalid because one of the parameter names is invalid
 * 1 A invalid because one of the parameter names is invalid
 *
 * 0 C equal
 * 0 D not equal
 *
 * 1 B not equal
 * 1 C equal
 * 1 D not equal
 *
 * 2 A equal
 * 2 B equal
 * 2 C equal
 * 2 D equal
 *
 * 3 A not equal
 * 3 B not equal
 * 3 C equal
 * 3 D not equal
 *
 */


struct comparison_test
{
	struct invalid_test : public logic_error
	{
		invalid_test(const string& msg): logic_error(msg) {}
	};

	enum long_name_setting
	{
	    no_long_name,
	    one_long_name,
	    long_names_equal,
	    long_names_unequal
	};

	enum short_name_setting
	{
	    no_short_name,
	    one_short_name,
	    short_names_equal,
	    short_names_unequal
	};

	long_name_setting long_setting;
	short_name_setting short_setting;

	comparison_test(long_name_setting l, short_name_setting s):
	    long_setting(l),
	    short_setting(s)
	{
	    if( long_setting == no_long_name && short_setting == no_short_name )
	    {
		throw invalid_test("invalid configuration: no long name and no short name");
	    }
	    else if( long_setting == no_long_name && short_setting == one_short_name )
	    {
		throw invalid_test("invalid configuration no long name and one short name");
	    }
	    else if( long_setting == one_long_name && short_setting == no_short_name )
	    {
		throw invalid_test("invalid configuration one long name and no short name");
	    }
	}

	bool equal_to_result() const
	{
	    if( long_setting == no_long_name && short_setting == short_names_equal )
	    {
		return true;
	    }
	    else if( long_setting == no_long_name && short_setting == short_names_unequal )
	    {
		return false;
	    }
	    else if( long_setting == one_long_name && short_setting == one_short_name )
	    {
		return false;
	    }
	    else if( long_setting == one_long_name && short_setting == short_names_equal )
	    {
		return true;
	    }
	    else if( long_setting == one_long_name && short_setting == short_names_unequal )
	    {
		return false;
	    }
	    else if( long_setting == long_names_equal )
	    {
		return true;
	    }
	    else if( long_setting == long_names_unequal && short_setting == no_short_name)
	    {
		return false;
	    }
	    else if( long_setting == long_names_unequal && short_setting == one_short_name)
	    {
		return false;
	    }
	    else if( long_setting == long_names_unequal && short_setting == short_names_equal)
	    {
		return true;
	    }
	    else if( long_setting == long_names_unequal && short_setting == short_names_unequal)
	    {
		return false;
	    }

	    throw invalid_test("unexpected configuration");
	}
};

struct test_failed
{
	test_failed(const parameter_name& n, string val, string t):
	    name(n), comp_value(val), test(t)
	{}

	parameter_name name;
	string comp_value;
	string test;
};

const string long_name = "long-name";
const string not_long_name = "not-long-name";
const string empty_string = "";

const char short_name = 's';
const char not_short_name = 't';
const string short_name_str(1, short_name);
const string not_short_name_str(1, not_short_name);

const int int_short_name = short_name;
const int int_not_short_name = not_short_name;


template <class T>
void test_parameter_name(const parameter_name& lhs, const T& name,
			 bool equality)
{
    stringstream ss;
    ss << name;

    if( (lhs == name) != equality )
    {
	throw test_failed(lhs, ss.str(), "lhs == name");
    }

    if( (lhs != name) == equality )
    {
	throw test_failed(lhs, ss.str(), "lhs != name");
    }

    return;
}

void test_short_name(const parameter_name& lhs)
{
    test_parameter_name(lhs, short_name, true);
    test_parameter_name(lhs, not_short_name, false);
    test_parameter_name(lhs, int_short_name, true);
    test_parameter_name(lhs, int_not_short_name, false);
    test_parameter_name(lhs, short_name_str, true);
    test_parameter_name(lhs, not_short_name_str, false);
    test_parameter_name(lhs, '\0', false);
}

void test_long_name(const parameter_name& lhs)
{
    test_parameter_name(lhs, long_name, true);
    test_parameter_name(lhs, long_name.c_str(), true);
    test_parameter_name(lhs, "", false);
    test_parameter_name(lhs, empty_string, false);

    return;
}

void test_long_names()
{
    parameter_name lhs1(long_name);
    parameter_name lhs2(long_name, short_name);

    test_long_name(lhs1);
    test_long_name(lhs2);

    return;
}

void test_short_names()
{
    parameter_name lhs1(long_name, short_name);
    parameter_name lhs2(short_name);

    test_short_name(lhs1);
    test_short_name(lhs2);
}



bool test_parameter_names(const parameter_name& lhs,
			  const parameter_name& rhs,
			  const comparison_test& test)
{
    bool equal_test = ( (lhs == rhs) == test.equal_to_result() );
    bool unequal_test = ( (lhs != rhs) != test.equal_to_result() );

    if( equal_test == false || unequal_test == false )
    {
	cerr << "test configuration: " << test.long_setting << ", "
	     << test.short_setting << ' ' << "failed: "
	     << "equal test result: " << equal_test << ", "
	     << "unequal test result: " << unequal_test << endl;

	return false;
    }

    return true;
}

typedef pair<comparison_test::long_name_setting,
	     comparison_test::short_name_setting> test_setup_t;

struct test_setup: public unary_function<test_setup_t, bool>
{
	bool operator()(const test_setup_t& setup) const
	{
	    comparison_test test(setup.first, setup.second);

	    parameter_name* lhs = NULL;
	    parameter_name* rhs = NULL;

	    if( test.long_setting == comparison_test::no_long_name )
	    {
		if( test.short_setting == comparison_test::short_names_equal )
		{
		    lhs = new parameter_name(short_name);
		    rhs = new parameter_name(short_name);
		}
		else if( test.short_setting == comparison_test::short_names_unequal )
		{
		    lhs = new parameter_name(short_name);
		    rhs = new parameter_name(not_short_name);
		}
	    }
	    else if( test.long_setting == comparison_test::one_long_name )
	    {
		if( test.short_setting == comparison_test::one_short_name )
		{
		    lhs = new parameter_name(long_name);
		    rhs = new parameter_name(short_name);
		}
		else if( test.short_setting == comparison_test::short_names_equal )
		{
		    lhs = new parameter_name(long_name, short_name);
		    rhs = new parameter_name(short_name);
		}
		else if( test.short_setting == comparison_test::short_names_unequal )
		{
		    lhs = new parameter_name(long_name, short_name);
		    rhs = new parameter_name(not_short_name);
		}
	    }
	    else if( test.long_setting == comparison_test::long_names_equal )
	    {
		if( test.short_setting == comparison_test::no_short_name )
		{
		    lhs = new parameter_name(long_name);
		    rhs = new parameter_name(long_name);
		}
		else if( test.short_setting == comparison_test::one_short_name )
		{
		    lhs = new parameter_name(long_name, short_name);
		    rhs = new parameter_name(long_name);
		}
		else if( test.short_setting == comparison_test::short_names_equal )
		{
		    lhs = new parameter_name(long_name, short_name);
		    rhs = new parameter_name(long_name, short_name);
		}
		else if( test.short_setting == comparison_test::short_names_unequal )
		{
		    lhs = new parameter_name(long_name, short_name);
		    rhs = new parameter_name(long_name, not_short_name);
		}
	    }
	    else if( test.long_setting == comparison_test::long_names_unequal )
	    {
		if( test.short_setting == comparison_test::no_short_name )
		{
		    lhs = new parameter_name(long_name);
		    rhs = new parameter_name(not_long_name);
		}
		else if( test.short_setting == comparison_test::one_short_name )
		{
		    lhs = new parameter_name(long_name, short_name);
		    rhs = new parameter_name(not_long_name);
		}
		else if( test.short_setting == comparison_test::short_names_equal )
		{
		    lhs = new parameter_name(long_name, short_name);
		    rhs = new parameter_name(not_long_name, short_name);
		}
		else if( test.short_setting == comparison_test::short_names_unequal )
		{
		    lhs = new parameter_name(long_name, short_name);
		    rhs = new parameter_name(not_long_name, not_short_name);
		}
	    }

	    if( lhs == NULL || rhs == NULL )
	    {
		delete lhs;
		delete rhs;
		cerr << "improper setup, either lhs is null, or rhs is null\n";
		return false;
	    }

	    bool ret = test_parameter_names(*lhs, *rhs, test);

	    delete lhs;
	    delete rhs;

	    return ret;
	}
};

int main()
{
    vector<test_setup_t> tests;

    tests.push_back(make_pair(comparison_test::no_long_name,
			      comparison_test::short_names_equal));

    tests.push_back(make_pair(comparison_test::no_long_name,
			      comparison_test::short_names_unequal));


    tests.push_back(make_pair(comparison_test::one_long_name,
			      comparison_test::one_short_name));

    tests.push_back(make_pair(comparison_test::one_long_name,
			      comparison_test::short_names_equal));

    tests.push_back(make_pair(comparison_test::one_long_name,
			      comparison_test::short_names_unequal));


    tests.push_back(make_pair(comparison_test::long_names_equal,
			      comparison_test::no_short_name));

    tests.push_back(make_pair(comparison_test::long_names_equal,
			      comparison_test::one_short_name));

    tests.push_back(make_pair(comparison_test::long_names_equal,
			      comparison_test::short_names_equal));

    tests.push_back(make_pair(comparison_test::long_names_equal,
			      comparison_test::short_names_unequal));


    tests.push_back(make_pair(comparison_test::long_names_unequal,
			      comparison_test::no_short_name));

    tests.push_back(make_pair(comparison_test::long_names_unequal,
			      comparison_test::one_short_name));

    tests.push_back(make_pair(comparison_test::long_names_unequal,
			      comparison_test::short_names_equal));

    tests.push_back(make_pair(comparison_test::long_names_unequal,
			      comparison_test::short_names_unequal));


    if( tests.end() != find_if(tests.begin(), tests.end(), not1(test_setup())) )
    {
	return 1;
    }

    try
    {
	test_short_names();
	test_long_names();
    }
    catch(test_failed& ex)
    {
	cerr << "test: " << ex.test << ' ' << "failed: "
	     << "long_name = " << ex.name.long_name() << ", "
	     << "short_name = " << ex.name.short_name() << ", "
	     << "comparison value = " << ex.comp_value << endl;

	return 1;
    }

    return 0;
}
