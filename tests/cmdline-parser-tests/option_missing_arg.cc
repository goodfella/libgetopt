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

    args.add(&opt);
    parser.add_option(&opt);

    parse_result res = parser.parse(args.count(), args);

    if( res.bad() != true )
    {
	cerr << "bad() is not true\n";
	return 1;
    }

    if( res.good() != false )
    {
	cerr << "good() is not false\n";
	return 1;
    }

    if( res.result() != parse_result::result_missing_arg )
    {
	cerr << "expected missing arg\n";
	return 1;
    }

    if( opt.name() != res.option_name() )
    {
	cerr << "incorrect option name: " << res.option_name() << endl;
	return 1;
    }

    return 0;
}
