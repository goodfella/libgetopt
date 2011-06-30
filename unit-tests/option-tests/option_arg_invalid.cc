#include <iostream>
#include <limits>

#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

int main(int argc, char** argv)
{
    option<int> opt("opt");
    cmdline_parser parser;
    cmdline_args args(argv[0]);

    args.add(&opt, static_cast<long long>(numeric_limits<int>::max()) + 1);
    parser.add_option(&opt);

    parse_result res = parser.parse(args.count(), args);

    if( res.result != parse_result::result_invalid_arg )
    {
	cerr << "parsing did not fail\n";
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

    if( opt.arg_valid() == true )
    {
	cerr << "arg_valid() is true\n";
	return 1;
    }

    return 0;
}
