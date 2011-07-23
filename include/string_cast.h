#ifndef __STRING_CAST_H__
#define __STRING_CAST_H__

#include <string>
#include <cerrno>
#include <cassert>
#include <limits>
#include <vector>
#include <list>

#include "strtonum.h"
#include "custom_parser.h"

namespace libgetopt
{
    struct parse_arg_failed {};

    struct parse_arg_passed {};

    // for all numeric types
    template<class Type>
    struct string_cast
    {
	    static bool cast(char const * const optarg, Type* argp, std::string* err_str);
    };

    template<class Type>
    bool string_cast<Type>::cast(char const * const optarg, Type* argp, std::string* err_str)
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

    template<class Type>
    struct string_cast<custom_parser<Type> >
    {
	    static bool cast(char const * const optarg,
			     custom_parser<Type>* param_parser,
			     std::string* err_str)
	    {
		Type& parser = param_parser->parser();
		return parser(optarg, err_str);
	    }
    };

    template<class Type>
    struct string_cast<std::vector<Type> >
    {
	    static bool cast(char const * const optarg, std::vector<Type>* vec,
			     std::string* err_str)
	    {
		Type arg;
		if( string_cast<Type>::cast(optarg, &arg, err_str) == true )
		{
		    vec->push_back(arg);
		    return true;
		}
		else
		{
		    return false;
		}
	    }
    };


    template<class Type>
    struct string_cast<std::list<Type> >
    {
	    static bool cast(char const * const optarg, std::list<Type>* li,
			     std::string* err_str)
	    {
		Type arg;
		if( string_cast<Type>::cast(optarg, &arg, err_str) == true )
		{
		    li->push_back(arg);
		    return true;
		}
		else
		{
		    return false;
		}
	    }
    };


    template<>
    struct string_cast<std::string>
    {
	    static bool cast(char const * const optarg, std::string* argp,
			     std::string* err_str)
	    {
		*argp = optarg;
		return true;
	    }
    };

    // For testing a parsing failure
    template<>
    struct string_cast<parse_arg_failed>
    {
	    static bool cast(char const * const optarg,
			     parse_arg_failed* param_parser,
			     std::string* err_str)
	    {
		return false;
	    }
    };

    // For testing a parsing success
    template<>
    struct string_cast<parse_arg_passed>
    {
	    static bool cast(char const * const optarg,
			     parse_arg_passed* param_parser,
			     std::string* err_str)
	    {
		return true;
	    }
    };
}

#endif
