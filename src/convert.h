#ifndef __CONVERT_H__
#define __CONVERT_H__

#include <cassert>
#include <cstdlib>
#include <string>

namespace libgetopt
{
    template<class Type>
    bool convert(char const * const optarg, Type* argp, std::string& error_str);

    template<>
    inline bool convert(char const* const optarg, int* argp,
			std::string& error_str)
    {
	assert(argp != NULL);
	*argp = atoi(optarg);
	return true;
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
    inline bool convert(char const * const optarg, long* argp,
			std::string& error_str)
    {
	assert(argp != NULL);
	*argp = atol(optarg);
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
