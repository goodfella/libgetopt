#ifndef __OPTIONAL_ARG_PARSER__
#define __OPTIONAL_ARG_PARSER__

#include "arg_parser.h"
#include "ibasic_flag.h"

namespace libgetopt
{
    class optional_arg_parser: public arg_parser, public ibasic_flag
    {
	public:

	virtual ~optional_arg_parser();

	optional_arg_parser();
    };

    inline optional_arg_parser::optional_arg_parser():
	arg_parser(arg_parser::arg_optional)
    {}
}

#endif
