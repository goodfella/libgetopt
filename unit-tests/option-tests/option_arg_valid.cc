#include <iostream>
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

int main(int argc, char** argv)
{
    option<int> opt("opt");
    cmdline_parser parser;
    cmdline_args args(argv[0]);

    args.add(&opt, "1");
    parser.add_option(&opt);

    parse_result res = parser.parse(args.count(), args);

    if( res.result != parse_result::result_success )
    {
	cerr << "parsing failed: " << res.error_string << endl;
	return 1;
    }

    if( opt.is_present() == false )
    {
	cerr << "is_present() is false\n";
	return 1;
    }

    if( opt.arg_present() == false )
    {
	cerr << "arg_present() is false\n";
	return 1;
    }

    if( opt.arg_valid() == false )
    {
	cerr << "arg_valid() is false\n";
	return 1;
    }

    return 0;
}
