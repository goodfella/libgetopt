#ifndef __CONVERT_H__
#define __CONVERT_H__

#include <string>
#include <errno.h>

namespace libgetopt
{
    template<class Ret, Ret (*Converter)(const char*, char**, int)>
    bool integral_convert(char const * const num_str,
			  std::string* err_str,
			  Ret* val,
			  Ret max,
			  Ret min,
			  int base)
    {
	assert( val != NULL );

	char* bad_chrs = NULL;

	errno = 0;

	Ret ret = Converter(num_str, &bad_chrs, base);

	if( errno == ERANGE )
	{
	    assert(ret >= max || ret <= min );

	    if( ret >= max )
	    {
		goto overflow;
	    }
	    else if( ret <= min )
	    {
		goto underflow;
	    }
	}
	else if( errno != 0 || *bad_chrs != '\0' )
	{
	    *err_str = "arg does not represent a numeric type";
	    return false;
	}
	else if( ret > max )
	{
	    goto overflow;
	}
	else if( ret < min )
	{
	    goto underflow;
	}

	*val = ret;
	return true;

      overflow:

	*err_str = "arg is too large";
	return false;

      underflow:

	*err_str = "arg is too small";
	return false;

    }

    bool signed_integral_convert(char const * const num_str,
				 std::string* err_str,
				 long long int* val,
				 long long int max,
				 long long int min,
				 int base);

    bool unsigned_integral_convert(char const * const num_str,
				   std::string* err_str,
				   unsigned long long int* val,
				   unsigned long long int max,
				   unsigned long long int min,
				   int base);

    template<class Type>
    bool convert(char const * const optarg, Type* argp, std::string* error_str);
}

#endif
