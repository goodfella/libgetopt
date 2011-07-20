#ifndef __NUMERIC_ARG_TEST_H__
#define __NUMERIC_ARG_TEST_H__

#include <cstdio>
#include "libunit-test.h"
#include "libgetopt.h"

namespace libgetopt
{
    namespace unit_tests
    {
	template<class T>
	struct numeric_arg_test
	{
		numeric_arg_test(char const * const a0, T a): arg0(a0), arg(a) {}

		char const * const arg0;
		T arg;

		bool run()
		{
		    option<T> opt('n');
		    cmdline_args args(arg0);

		    args.add("-n");
		    args.add(arg);

		    cmdline_parser parser;

		    parser.add_option(&opt);

		    parse_result res;

		    res = parser.parse(args.count(), args);

		    if( res.bad() )
		    {
			return false;
		    }
		    else if( opt.arg() != arg )
		    {
			return false;
		    }

		    return true;
		}
	};
    }
}
#endif
