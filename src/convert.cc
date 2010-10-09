#include <cstdlib>
#include <limits>
#include <cassert>
#include <string>

#include "convert.h"

using std::numeric_limits;
using std::string;

namespace libgetopt
{
    bool signed_integral_convert(char const * const num_str,
				 string* err_str,
				 long long int* val,
				 long long int max,
				 long long int min, int base)
    {
	return integral_convert<long long int, strtoll>(num_str,
							err_str,
							val,
							max,
							min,
							base);
    }

    bool unsigned_integral_convert(char const * const num_str,
				   string* err_str,
				   unsigned long long int* val,
				   unsigned long long int max,
				   unsigned long long int min,
				   int base)
    {
	return integral_convert<unsigned long long int, strtoull>(num_str,
								  err_str,
								  val,
								  max,
								  min,
								  base);
    }

    template<>
    bool convert(char const* const optarg, int* argp,
		 string* error_str)
    {
	assert(argp != NULL);

	long long int val;

	if( signed_integral_convert(optarg, error_str, &val,
				    numeric_limits<int>::max(),
				    numeric_limits<int>::min(),
				    10) == true )
	{
	    *argp = static_cast<int>(val);
	    return true;
	}

	return false;
    }


    template<>
    bool convert(char const * const optarg, long* argp,
		 string* error_str)
    {
	assert(argp != NULL);

	long long int val;

	if( signed_integral_convert(optarg, error_str, &val,
				    numeric_limits<long>::max(),
				    numeric_limits<long>::min(),
				    10) == true )
	{
	    *argp = static_cast<long>(val);
	    return true;
	}

	return false;
    }


    template<>
    bool convert(char const * const optarg, double* argp,
		 std::string* error_str)
    {
	assert(argp != NULL);
	*argp = atof(optarg);
	return true;
    }


    template<>
    bool convert(char const * const optarg, long long* argp,
		 std::string* error_str)
    {
	assert(argp != NULL);
	*argp = atoll(optarg);
	return true;
    }

    template<>
    bool convert(char const * const optarg, std::string* argp,
		 std::string* error_str)
    {
	assert(argp != NULL);
	*argp = optarg;
	return true;
    }
}
