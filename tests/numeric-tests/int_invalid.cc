#include <cstdio>

#include "libgetopt.h"
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

int main(int argc, char** argv)
{
    invalid_numeric_test<int> test(argv[0]);

    if( test.run("abc123") == false )
    {
	return 1;
    }

    return 0;
}
