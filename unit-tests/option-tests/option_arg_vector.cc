#include <vector>
#include <string>
#include <iostream>

#include "libgetopt.h"
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

int main(int argc, char ** argv)
{
    option<vector<string> > opt("opt");
    cmdline_parser parser;
    cmdline_args args(argv[0]);

    args.add(&opt, "123");
    args.add(&opt, "456");
    args.add(&opt, "789");

    parser.add_option(&opt);

    parser.parse(args.count(), args);

    option<vector<string> >::arg_type_t::const_iterator i;

    int j = 2;
    for(i = opt.get_arg().begin(); i != opt.get_arg().end(); ++i, j+=2)
    {
	if( (*i == args[j]) != true )
	{
	    cerr << "vector args missmatch\n";
	    return 1;
	}

    }

    return 0;
}
