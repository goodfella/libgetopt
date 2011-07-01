#ifndef __CONVERT_H__
#define __CONVERT_H__

#include <string>
#include <cerrno>
#include <cassert>
#include <limits>

#include "strtonum.h"

namespace libgetopt
{
    template<class Type>
    bool string_cast(char const * const optarg, Type* argp,
			     std::string* err_str);

    template<>
    inline bool string_cast(char const * const optarg, std::string* argp,
			    std::string* err_str)
    {
	*argp = optarg;
	return true;
    };

    // for all numeric types
    template<class Type>
    bool string_cast(char const * const optarg, Type* argp, std::string* err_str)
    {
	typedef std::numeric_limits<Type> numeric_limits_t;

	typedef strtonum_traits<numeric_limits_t::is_signed,
	    strtonum_is_float<Type>::value,
	    strtonum_is_double<Type>::value > traits_t;

	static const typename traits_t::numeric_t max = numeric_limits_t::max();
	static const typename traits_t::numeric_t min = numeric_limits_t::min();
	static const bool is_integer = numeric_limits_t::is_integer;

	typename traits_t::numeric_t val;

	if( strtonum<is_integer, traits_t>::convert(optarg, err_str, max, min, &val) == true )
	{
	    *argp = static_cast<Type>(val);
	    return true;
	}
	else
	{
	    return false;
	}
    }
}

#endif
