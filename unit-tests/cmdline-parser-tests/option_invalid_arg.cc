#include <iostream>
#include <limits>
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

int main(int argc, char** argv)
{
    option<char> opt("opt");
    cmdline_parser parser;
    cmdline_args args(argv[0]);

    args.add(&opt, static_cast<int>(numeric_limits<char>::max() + 1));
    parser.add_option(&opt);

    parse_result res = parser.parse(args.count(), args);

    if( res.result() != parse_result::result_invalid_arg )
    {
	cerr << "expected missing arg\n";
	return 1;
    }

    if( opt.name() != res.option_name() )
    {
	cerr << "incorrect option name: " << res.option_name() << endl;
	return 1;
    }

    if( res.invalid_arg() != args[args.count() - 1] )
    {
	cerr << "incorrect invalid arg: " << res.invalid_arg() << endl;
	return 1;
    }

    return 0;
}
