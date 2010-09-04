#ifndef __CONVERT_H__
#define __CONVERT_H__

#include <cassert>
#include <cstdlib>
#include <string>

namespace libgetopt
{
    template<class Type>
    bool convert(char const * const optarg, Type* argp);

    template<>
    inline bool convert(char const* const optarg, int* argp)
    {
	assert(argp != NULL);
	*argp = atoi(optarg);
	return true;
    }

    template<>
    inline bool convert(char const * const optarg, double* argp)
    {
	assert(argp != NULL);
	*argp = atof(optarg);
	return true;
    }

    template<>
    inline bool convert(char const * const optarg, long* argp)
    {
	assert(argp != NULL);
	*argp = atol(optarg);
	return true;
    }

    template<>
    inline bool convert(char const * const optarg, long long* argp)
    {
	assert(argp != NULL);
	*argp = atoll(optarg);
	return true;
    }

    template<>
    inline bool convert(char const * const optarg, std::string* argp)
    {
	assert(argp != NULL);
	*argp = optarg;
	return true;
    }
}

#endif
