#ifndef __NUMERIC_UNDERFLOW_TEST_H__
#define __NUMERIC_UNDERFLOW_TEST_H__

#include <limits>

#include "invalid_numeric_test.h"

namespace libgetopt
{
    namespace unit_tests
    {

	template<class T>
	class numeric_underflow_test: protected invalid_numeric_test<T>
	{
	    public:

		numeric_underflow_test(char* arg0);

		bool run();
	};

	template<class T>
	numeric_underflow_test<T>::numeric_underflow_test(char* arg0):
	    invalid_numeric_test<T>(arg0)
	{}

	template<class T>
	bool numeric_underflow_test<T>::run()
	{
	    long long arg = std::numeric_limits<T>::min();
	    arg--;

	    return invalid_numeric_test<T>::run(arg);
	}
    }
}

#endif
