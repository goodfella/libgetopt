#include <cstdio>

#include "libgetopt.h"
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

int main(int argc, char** argv)
{
    cmdline_args args;

    option<int> int_opt("int");

    cmdline_parser parser;

    parser.add_option(&int_opt);

    args.add(argv[0]);

    args.add(&int_opt, "1234abcd");

    unit_test test("invalid argument", args.count(), args, parser,
		   cmdline_parser::parse_result::result_invalid_arg);


    if( test.run() == false )
    {
	printf("%s: failed\n", test.name.c_str());
	return 1;
    }

    return 0;
}