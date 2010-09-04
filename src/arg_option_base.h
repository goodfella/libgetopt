#ifndef __ARG_OPTION_BASE_H__
#define __ARG_OPTION_BASE_H__

#include "option_base.h"


namespace libgetopt
{
    class arg_option_base : public option_base
    {
	public:

	    arg_option_base(const char short_opt);
	    arg_option_base(const std::string& long_opt);
	    arg_option_base(const std::string& long_opt, const char opt);

	    virtual ~arg_option_base();

	    virtual bool set(char const * const optarg);

	    argument_policy_t arg_policy() const;

	    bool arg_is_valid() const;

	private:

	    virtual bool parse_arg(const char* const optarg) = 0;

	    bool m_valid_arg;
    };
}

inline libgetopt::arg_option_base::arg_option_base(const char short_opt):
    option_base(short_opt),
    m_valid_arg(true)
{}


inline libgetopt::arg_option_base::arg_option_base(const std::string& long_opt):
    option_base(long_opt, 0),
    m_valid_arg(true)
{}


inline libgetopt::arg_option_base::arg_option_base(const std::string& long_opt, const char short_opt):
    option_base(long_opt, short_opt),
    m_valid_arg(true)
{}


inline bool libgetopt::arg_option_base::set(char const * const optarg)
{
    option_base::set();

    if( optarg != NULL )
    {
	m_valid_arg = parse_arg(optarg);
    }

    return m_valid_arg;
}

inline bool libgetopt::arg_option_base::arg_is_valid() const
{
    return m_valid_arg;
}

#endif
