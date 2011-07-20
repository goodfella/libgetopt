#ifndef __DELIMITED_ARG_H__
#define __DELIMITED_ARG_H__

#include "custom_parser.h"
#include "delimited_arg_parser.h"

namespace libgetopt
{
    /// Convenient wrapper for delimited types
    template<class Type>
    struct delimited_arg
    {
	    typedef custom_parser<delimited_arg_parser<Type> > type_t;
    };
}

#endif
