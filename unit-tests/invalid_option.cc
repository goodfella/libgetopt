#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

#include "libgetopt.h"
#include "libunit-test.h"

using namespace libgetopt;
using namespace libgetopt::unit_tests;

using namespace std;

class option_test
{
    public:

	option_test(string n, string l):
	    name(n),
	    long_opt(l),
	    short_opt('\0'),
	    has_long(true),
	    has_short(false)
	{}

	option_test(string n, string l, char s):
	    name(n),
	    long_opt(l),
	    short_opt(s),
	    has_long(true),
	    has_short(true)
	{}

	option_test(string n, char s):
	    name(n),
	    long_opt(""),
	    short_opt(s),
	    has_long(false),
	    has_short(true)
	{}

	void operator()() const
	{
	    if( has_long && has_short )
	    {
		option<int> opt(long_opt, short_opt);
	    }
	    else if( has_long )
	    {
		option<int> opt(long_opt);
	    }
	    else if( has_short )
	    {
		option<int> opt(short_opt);
	    }
	}

    	string name;

    private:

	string long_opt;
	char short_opt;
	bool has_long;
	bool has_short;
};

typedef vector< option_test > test_list_t;

int main()
{

    test_list_t tests;

    tests.push_back(option_test("null long", ""));
    tests.push_back(option_test("null short", '\0'));
    tests.push_back(option_test("null long short", "", 'i'));
    tests.push_back(option_test("null short long", "int", '\0'));
    tests.push_back(option_test("null long null short", "", '\0'));

    tests.push_back(option_test("non graphical long", "\t"));
    tests.push_back(option_test("non graphical short", '\t'));
    tests.push_back(option_test("non graphical long short", "\t", 'i'));
    tests.push_back(option_test("non graphical short long", "int", '\t'));
    tests.push_back(option_test("non graphical long non graphical short", "\t", '\t'));

    tests.push_back(option_test("dashed long", "-long"));
    tests.push_back(option_test("dashed short", '-'));
    tests.push_back(option_test("dashed long short", "-long", 's'));
    tests.push_back(option_test("dashed short long", "long", '-'));
    tests.push_back(option_test("dashed long dashed short", "-long", '-'));


    test_list_t::const_iterator failed_test = find_if(tests.begin(),
						      tests.end(),
						      not1(expected_exception<invalid_option,
							   option_test>()));

    if( failed_test != tests.end() )
    {
	printf("test: %s, failed\n", failed_test->name.c_str());
	return 1;
    }

    return 0;
}
