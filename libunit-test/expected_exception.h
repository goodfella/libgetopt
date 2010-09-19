#ifndef __EXPECTED_EXCEPTION_H__
#define __EXPECTED_EXCEPTION_H__

#include <functional>


namespace libgetopt
{
    namespace unit_tests
    {
	template<class Ex, class Fun>
	struct expected_exception: public std::unary_function<Fun, bool>
	{
	    bool operator () (Fun fun) const
	    {
		try
		{
		    fun();
		}
		catch(Ex& ex)
		{
		    return true;
		}
		catch(...)
		{
		    return false;
		}

		return false;
	    }
	};
    }
}

#endif
