#include <string>
#include <cerrno>
#include <cassert>

#include "strtonum.h"

using namespace std;

namespace libgetopt
{
    bool strtonum_result(string* err_str,
			 char const * const bad_chars,
			 int errno_val,
			 bool overflow,
			 bool underflow)
    {
	if( errno_val == ERANGE )
	{
	    assert(overflow == true || underflow == true );

	    if( overflow == true )
	    {
		goto overflow;
	    }
	    else if( underflow ==true )
	    {
		goto underflow;
	    }
	}
	else if( errno_val != 0 || *bad_chars != '\0' )
	{
	    *err_str = "arg does not represent a numeric type";
	    return false;
	}
	else if( overflow == true )
	{
	    goto overflow;
	}
	else if( underflow == true )
	{
	    goto underflow;
	}
	else
	{
	    return true;
	}

      overflow:

	*err_str = "arg is too large";
	return false;

      underflow:

	*err_str = "arg is too small";
	return false;
    }
}
