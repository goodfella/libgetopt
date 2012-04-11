#include <iostream>
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

int main(int argc, char** argv)
{
    option<parse_arg_passed> opt("opt");
    cmdline_parser parser;
    cmdline_args args(argv[0]);

    args.add("--abc");
    parser.add_option(&opt);

    parse_result res = parser.parse(args.count(), args);

    if( res.result() != parse_result::result_invalid_option )
    {
	cerr << "expected invalid option\n";
	return 1;
    }

    if( res.param_name() != "abc" )
    {
	cerr << "incorrect invalid option: " << res.param_name() << endl;
	return 1;
    }

    return 0;
}
