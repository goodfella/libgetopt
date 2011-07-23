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

    args.add(&opt, "1");
    parser.add_option(&opt);

    parser.parse(args.count(), args);

    if( opt.present() == false )
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
