#ifndef __GETOPT_OPTION_H__
#define __GETOPT_OPTION_H__

#include <getopt.h>
#include <string>

namespace libgetopt
{
    struct getopt_option
    {
	    ::option opt;
	    std::string optstring;
    };
}

#endif
