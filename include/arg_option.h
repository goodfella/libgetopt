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

	    explicit arg_option(const char short_opt);
	    explicit arg_option(const std::string& long_opt);
	    arg_option(const std::string& long_opt, const char opt);

	    virtual ~arg_option();

	    void present();
	    bool is_present() const;

	    virtual bool parse_arg(char const * const optarg, std::string& err_str);
	    bool is_set() const;

	    argument_policy_t arg_policy() const;

	    bool arg_is_valid() const;

	protected:

	    virtual void fill_option(getopt_option* opt) const;

	    bool m_valid_arg;
	    bool m_is_present;

	private:

	    virtual bool parse(char const * const optarg, std::string& err_str) = 0;
    };
}

inline libgetopt::arg_option::arg_option(const char short_opt):
    option_base(short_opt),
    m_valid_arg(false),
    m_is_present(false)
{}


inline libgetopt::arg_option::arg_option(const std::string& long_opt):
    option_base(long_opt, 0),
    m_valid_arg(false),
    m_is_present(false)
{}


inline libgetopt::arg_option::arg_option(const std::string& long_opt,
					 const char short_opt):
    option_base(long_opt, short_opt),
    m_valid_arg(false),
    m_is_present(false)
{}

inline void libgetopt::arg_option::present()
{ m_is_present = true; }

inline bool libgetopt::arg_option::is_present() const
{
    return m_is_present;
}

inline bool libgetopt::arg_option::is_set() const
{
    return (m_is_present == true && m_valid_arg == true);
}

inline bool libgetopt::arg_option::arg_is_valid() const
{
    return m_valid_arg;
}

inline libgetopt::argument_policy_t libgetopt::arg_option::arg_policy() const
{
    return arg_policy_required;
}

#endif
