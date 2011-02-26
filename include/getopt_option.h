#ifndef __GETOPT_OPTION_H__
#define __GETOPT_OPTION_H__

#include <getopt.h>
#include <string>

namespace libgetopt
{
    class option_base;

    class getopt_option: public ::option
    {
	public:

	    getopt_option(option_base const * const opt);
	    std::string optstring;
    };
}

#endif
