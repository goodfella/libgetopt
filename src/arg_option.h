#ifndef __ARG_OPTION_H__
#define __ARG_OPTION_H__

#include "option_base.h"


namespace libgetopt
{
    class arg_option : public option_base
    {
	public:

	    arg_option(char opt);
	    arg_option(const std::string name, int val, bool use_flag = false);
	    arg_option(const std::string name, char opt);

	    virtual ~arg_option(){}

	    bool set(const char* const optarg);

	protected:

	    const std::string get_optstring() const;
	    struct ::option* get_option();

	private:

	    virtual bool parse_arg(const char* const optarg) = 0;
    };
}

inline libgetopt::arg_option::arg_option(char opt):
    option_base(opt)
{}


inline libgetopt::arg_option::arg_option(const std::string name, int val,
					 bool use_flag):
    option_base(name, val, use_flag)
{}


inline libgetopt::arg_option::arg_option(const std::string name, char opt):
    option_base(name, opt)
{}


inline bool libgetopt::arg_option::set(const char* const optarg)
{
    libgetopt::option_base::set();
    return parse_arg(optarg);
}

#endif


