#ifndef __ARG_OPTION_H__
#define __ARG_OPTION_H__

#include <string>
#include "option_base.h"


namespace libgetopt
{
    enum argument_policy_t
    {
	arg_policy_none,
	arg_policy_required,
	arg_policy_optional
    };


    class arg_option : public option_base
    {
	public:

	    enum parse_status_t
	    {
		no_parse,
		parse_failed,
		parse_succeeded
	    };

	    explicit arg_option(const char short_opt);
	    explicit arg_option(const std::string& long_opt);
	    arg_option(const std::string& long_opt, const char opt);

	    virtual ~arg_option();

	    bool present() const;
	    bool arg_set() const;
	    bool bad_arg() const;
	    argument_policy_t arg_policy() const;
	    parse_status_t parse_status() const;

	    virtual bool parse_arg(char const * const optarg, std::string* err_str);

	protected:

	    virtual void fill_option(getopt_option* opt) const;
	    void present(bool is_present);
	    void parse_status(parse_status_t status);

	private:

	    virtual bool parse(char const * const optarg, std::string* err_str) = 0;

	    bool m_is_present;
	    parse_status_t m_parse_status;
    };
}

inline libgetopt::arg_option::arg_option(const char short_opt):
    option_base(short_opt),
    m_is_present(false),
    m_parse_status(no_parse)
{}


inline libgetopt::arg_option::arg_option(const std::string& long_opt):
    option_base(long_opt, 0),
    m_is_present(false),
    m_parse_status(no_parse)
{}


inline libgetopt::arg_option::arg_option(const std::string& long_opt,
					 const char short_opt):
    option_base(long_opt, short_opt),
    m_is_present(false),
    m_parse_status(no_parse)
{}

inline bool libgetopt::arg_option::present() const
{
    return m_is_present;
}

inline void libgetopt::arg_option::present(bool is_present)
{
    m_is_present = is_present;
}

inline libgetopt::argument_policy_t libgetopt::arg_option::arg_policy() const
{
    return arg_policy_required;
}

inline libgetopt::arg_option::parse_status_t libgetopt::arg_option::parse_status() const
{
    return m_parse_status;
}

inline void libgetopt::arg_option::parse_status(libgetopt::arg_option::parse_status_t status)
{
    m_parse_status = status;
}

inline bool libgetopt::arg_option::arg_set() const
{
    return (m_parse_status == libgetopt::arg_option::parse_succeeded);
}

inline bool libgetopt::arg_option::bad_arg() const
{
    return (m_parse_status == libgetopt::arg_option::parse_failed);
}

#endif
