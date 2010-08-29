#ifndef __ARG_OPTION_BASE_H__
#define __ARG_OPTION_BASE_H__

#include "option_base.h"


namespace libgetopt
{
    class arg_option_base : public option_base
    {
	public:

	    arg_option_base(char opt);
	    arg_option_base(const std::string& name, int val);
	    arg_option_base(const std::string& name, char opt);

	    virtual ~arg_option_base(){}

	    bool set(const char* const optarg);

	protected:

	    const std::string get_optstring() const;
	    struct ::option* get_option();

	private:

	    virtual bool parse_arg(const char* const optarg) = 0;
    };
}

inline libgetopt::arg_option_base::arg_option_base(char opt):
    option_base(opt)
{}


inline libgetopt::arg_option_base::arg_option_base(const std::string& name, int val):
    option_base(name, val)
{}


inline libgetopt::arg_option_base::arg_option_base(const std::string& name, char opt):
    option_base(name, opt)
{}


inline bool libgetopt::arg_option_base::set(const char* const optarg)
{
    libgetopt::option_base::set();
    return parse_arg(optarg);
}

#endif


