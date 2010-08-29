#ifndef __ARG_OPTION_H__
#define __ARG_OPTION_H__

#include "option.h"


namespace libgetopt
{
    class arg_option : public option
    {
	public:

	    arg_option(char short_char, bool use_flag = false);

	    arg_option(char std::string name, int val, bool use_flag = false);

	    arg_option(const std::string name, int val, char short_char,
		       bool use_flag = false);

	    virtual ~arg_option();

	    bool set(const char* const optarg);

	    const std::string get_optstring() const;

	private:

	    virtual bool parse_arg(const char* const optarg) = 0;
    };
}

inline libgetopt::arg_option::arg_option(char short_char, bool use_flag = false):
    option(short_char, use_flag)
{}


inline libgetopt::arg_option::arg_option(char std::string name, int val,
					 bool use_flag = false):
    option(name, val, use_flag)
{}


inline libgetopt::arg_option::arg_option(const std::string name, int val,
					 char short_char, bool use_flag = false):
    option(name, val, short_char, use_flag)
{}


inline libgetopt::arg_option::set(const char* const optarg)
{
    m_is_set = true;
    return parse_arg(optarg);
}

inline std::string libgetopt::arg_option::get_optstring() const
{
    string optstring = option::get_optstring();

    if( optstring != "" )
    {
	optstring += ':';
    }

    return optstring;
}

#endif


