#ifndef __ARG_OPTION_BASE_H__
#define __ARG_OPTION_BASE_H__

#include "option_base.h"


namespace libgetopt
{
    class arg_option_base : public option_base
    {
	public:

	    arg_option_base(char short_opt);
	    arg_option_base(const std::string& long_opt, int val);
	    arg_option_base(const std::string& long_opt, char opt);

	    virtual ~arg_option_base();

	    bool set(char const * const optarg);

	    argument_policy_t arg_policy() const;

	private:

	    virtual bool parse_arg(const char* const optarg) = 0;
    };
}

inline libgetopt::arg_option_base::arg_option_base(char short_opt):
    option_base(short_opt)
{}


inline libgetopt::arg_option_base::arg_option_base(const std::string& long_opt, int val):
    option_base(long_opt, val)
{}


inline libgetopt::arg_option_base::arg_option_base(const std::string& long_opt, char short_opt):
    option_base(long_opt, short_opt)
{}


inline bool libgetopt::arg_option_base::set(char const * const optarg)
{
    option_base::set();
    return parse_arg(optarg);
}

#endif
