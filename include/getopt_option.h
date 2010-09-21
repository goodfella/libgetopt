#ifndef __GETOPT_OPTION_H__
#define __GETOPT_OPTION_H__

#include <getopt.h>
#include <string>

namespace libgetopt
{
    struct getopt_option: public ::option
    {
	    std::string optstring;
    };
}

#endif
