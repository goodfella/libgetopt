#include "libgetopt.h"
#include "libunit-test.h"

using namespace libgetopt;
using namespace unit_tests;

int main()
{
    option<parse_arg_passed> iopt("int", 'i');
    cmdline_parser parser;
    cmdline_args args;

    args.add("--int");

    parser.add_option(&iopt);

    parser.parse(args.count(), args);

    try
    {
	parser.parse(args.count(), args);
    }
    catch( parser_in_use& ex )
    {
	return 0;
    }

    return 1;
}
