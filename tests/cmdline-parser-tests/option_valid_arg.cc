#include <iostream>
#include <limits>
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

int main(int argc, char** argv)
{
    option<parse_arg_passed> opt("opt");
    cmdline_parser parser;
    cmdline_args args(argv[0]);

    args.add(&opt, "good-arg");
    parser.add_option(&opt);

    parse_result res = parser.parse(args.count(), args);

    if( res.bad() != false )
    {
	cerr << "bad() is not false\n";
	return 1;
    }

    if( res.good() != true )
    {
	cerr << "good() is not true\n";
	return 1;
    }

    if( res.result() != parse_result::result_success )
    {
	cerr << "expected success\n";
	return 1;
    }

    return 0;
}
