#ifndef __CONVERT_H__
#define __CONVERT_H__

#include <errno.h>
#include <cstdlib>
#include <limits>
#include <cassert>
#include <string>


namespace libgetopt
{
    template< class Type,
	      class Func_Ret,
	      class Func_Type,
	      Func_Type Func,
	      int Errno >
    struct converter_info_base
    {
	    typedef Func_Ret func_return_t;
	    static Func_Type func;
	    static Type overflow_val;
	    static Type underflow_val;
	    static int range_errno;
    };

    template< class Type,
	      class Func_Ret,
	      class Func_Type,
	      Func_Type Func,
	      int Errno >
    Func_Type converter_info_base<Type, Func_Ret, Func_Type, Func, Errno>::func = Func;

    template< class Type,
	      class Func_Ret,
	      class Func_Type,
	      Func_Type Func,
	      int Errno >
    Type converter_info_base<Type, Func_Ret, Func_Type, Func, Errno>::overflow_val =
	std::numeric_limits<Type>::max();

    template< class Type,
	      class Func_Ret,
	      class Func_Type,
	      Func_Type Func,
	      int Errno >
    Type converter_info_base<Type, Func_Ret, Func_Type, Func, Errno>::underflow_val =
	std::numeric_limits<Type>::min();


    template< class Type,
	      class Func_Ret,
	      class Func_Type,
	      Func_Type Func,
	      int Errno >
    int converter_info_base<Type, Func_Ret, Func_Type, Func, Errno>::range_errno = Errno;



    template< class Type >
    struct converter_info;

    template<>
    struct converter_info<int>: public converter_info_base<int,
							   long,
							   long (*)(char const * const, char**, int),
							   &strtol,
							   ERANGE>
    {
	    static int base;
    };

    int converter_info<int>::base = 10;


    template<>
    struct converter_info<long>: public converter_info_base<long,
							    long,
							    long (*)(char const * const, char**, int),
							    &strtol,
							    ERANGE>

    {
	    static int base;
    };

    int converter_info<long>::base = 10;


    template<class Type>
    bool integral_convert(char const * const num_str, std::string& err_str,
			  Type* val)
    {
	assert( val != NULL );

	char* bad_chrs = NULL;

	errno = 0;

	typename converter_info<Type>::func_return_t ret;

	ret = converter_info<Type>::func(num_str,
					 &bad_chrs,
					 converter_info<Type>::base);

	if( errno == converter_info<Type>::range_errno )
	{
	    assert(ret >= converter_info<Type>::overflow_val ||
		   ret <= converter_info<Type>::underflow_val );

	    if( ret >= converter_info<Type>::overflow_val )
	    {
		err_str = "arg is too large";
		return false;
	    }
	    else if( ret <= converter_info<Type>::underflow_val )
	    {
		err_str = "arg is too small";
		return false;
	    }
	}
	else if( *bad_chrs != '\0' )
	{
	    err_str = "arg does not represent a numeric type";
	    return false;
	}

	*val = ret;
	return true;
    }


    template<class Type>
    bool convert(char const * const optarg, Type* argp, std::string& error_str);

    template<>
    inline bool convert(char const* const optarg, int* argp,
			std::string& error_str)
    {
	assert(argp != NULL);

	return integral_convert<int>(optarg, error_str, argp);
    }


    template<>
    inline bool convert(char const * const optarg, long* argp,
			std::string& error_str)
    {
	assert(argp != NULL);

	return integral_convert<long>(optarg, error_str, argp);
    }


    template<>
    inline bool convert(char const * const optarg, double* argp,
			std::string& error_str)
    {
	assert(argp != NULL);
	*argp = atof(optarg);
	return true;
    }


    template<>
    inline bool convert(char const * const optarg, long long* argp,
			std::string& error_str)
    {
	assert(argp != NULL);
	*argp = atoll(optarg);
	return true;
    }

    template<>
    inline bool convert(char const * const optarg, std::string* argp,
			std::string& error_str)
    {
	assert(argp != NULL);
	*argp = optarg;
	return true;
    }
}

#endif
