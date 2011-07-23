#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "libgetopt.h"

using namespace std;
using namespace libgetopt;

typedef delimited_arg_parser<string> dparser_t;
typedef custom_parser<dparser_t> cparser_t;

struct test_failed: public logic_error
{
	test_failed(): logic_error("test failed") {}
};

void check_parsers(const cparser_t& lhs, const cparser_t& rhs)
{
    if( lhs.parser().args().size() != rhs.parser().args().size() )
    {
	cerr << "parser args are not equal in size\n";
	throw test_failed();
    }

    if( equal(lhs.parser().args().begin(),
	      lhs.parser().args().end(),
	      rhs.parser().args().begin()) == false )
    {
	cerr << "parser args are not equal\n";
	throw test_failed();
    }
}

int main()
{
    dparser_t dparser;

    for(char i = 48; i < 58; ++i)
    {
	dparser.args().push_back(string(1,i));
    }

    cparser_t cparser0;
    cparser_t cparser1(dparser);
    cparser_t cparser2(cparser1);
    cparser_t cparser3;

    cparser0.parser(dparser);
    cparser3 = cparser1;

    try
    {
	check_parsers(cparser0, cparser1);
	check_parsers(cparser0, cparser2);
	check_parsers(cparser0, cparser3);

	check_parsers(cparser1, cparser2);
	check_parsers(cparser1, cparser3);

	check_parsers(cparser2, cparser3);
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

    return 0;
}
