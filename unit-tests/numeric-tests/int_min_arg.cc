#include <limits>

#include "libunit-test.h"

using namespace libgetopt;
using namespace libgetopt::unit_tests;

int main(int argc, char** argv)
{
    numeric_arg_test<int> test(argv[0], std::numeric_limits<int>::min());

    if( test.run() == false )
    {
	return 1;
    }

    return 0;
}
