#ifndef __CMDLINE_TOKEN_H__
#define __CMDLINE_TOKEN_H__

#include <string>

namespace libgetopt
{
    struct cmdline_token
    {
	    enum token_type_t
	    {
		long_named,
		short_named,
		unnamed
	    };

	    cmdline_token();

	    std::string parameter;
	    std::string name;
	    std::string arg;
	    token_type_t type;
    };

    inline cmdline_token::cmdline_token():
	parameter(""),
	name(""),
	arg("")
    {}
}

#endif
