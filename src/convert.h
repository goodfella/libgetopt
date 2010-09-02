#ifndef __CONVERT_H__
#define __CONVERT_H__

#include <cstdlib>
#include <string>

namespace libgetopt
{
    template<class Type>
    Type convert(char const * const optarg);

    template<>
    inline int convert(char const* const optarg)
    {
	return atoi(optarg);
    }

    template<>
    inline double convert(char const * const optarg)
    {
 	return atof(optarg);
    }

    template<>
    inline long convert(char const * const optarg)
    {
	return atol(optarg);
    }

    template<>
    inline long long convert(char const * const optarg)
    {
	return atoll(optarg);
    }

    template<>
    inline std::string convert(char const * const optarg)
    {
	return optarg;
    }
}

#endif
