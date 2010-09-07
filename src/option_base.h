#ifndef __OPTION_BASE_H__
#define __OPTION_BASE_H__

#include <cassert>
#include <string>
#include <stdexcept>


namespace libgetopt
{
    enum argument_policy_t
    {
	arg_policy_none,
	arg_policy_required,
	arg_policy_optional
    };

    class invalid_option: public std::logic_error
    {
	public:

	    invalid_option(const std::string& option):
		std::logic_error("invalid option: " + option)
	    {}
    };

    class option_base
    {
	    friend class getopt_option;
	    friend class cmdline_parser;

	public:

	    typedef bool (option_base::*val_predicate_t)(int) const;
	    typedef bool (option_base::*long_opt_predicate_t)(char const *) const;
	    typedef bool (option_base::*short_opt_predicate_t)(char) const;

	    static const short_opt_predicate_t short_opt_pred;
	    static const long_opt_predicate_t long_opt_pred;
	    static const val_predicate_t val_pred;

	    explicit option_base(const char short_opt);
	    option_base(const std::string& long_opt, const int val);
	    option_base(const std::string& long_opt, const char opt);

	    virtual ~option_base();

	    bool matches(int check_val) const;
	    bool matches(char const * name) const;
	    bool matches(char short_opt) const;

	    bool has_long_option() const;
	    bool has_short_option() const;

	    const std::string& long_option() const;
	    const char short_option() const;
	    int val() const;

	    virtual argument_policy_t arg_policy() const = 0;

	protected:

	    virtual int* flag_ptr();
	    void set_val(const int val);

	private:

	    const char m_short_opt;
	    const std::string m_long_opt;
	    int m_val;
    };
}

inline libgetopt::option_base::option_base(const char short_opt):
    m_short_opt(short_opt),
    m_long_opt(""),
    m_val(short_opt)
{
    if( short_opt == '\0' )
    {
	throw invalid_option("null short option");
    }
}

inline libgetopt::option_base::option_base(const std::string& long_opt, int val):
    m_short_opt('\0'),
    m_long_opt(long_opt),
    m_val(val)
{
    if( long_opt == "" )
    {
	throw invalid_option("null long option");
    }
}

inline libgetopt::option_base::option_base(const std::string& long_opt, const char short_opt):
    m_short_opt(short_opt),
    m_long_opt(long_opt),
    m_val(short_opt)
{
    if( long_opt == "")
    {
	throw invalid_option("null long option");
    }

    if( short_opt == '\0' )
    {
	throw invalid_option("null short option");
    }
}

inline bool libgetopt::option_base::matches(int val) const
{
    return val == m_val;
}

inline bool libgetopt::option_base::matches(char const * name) const
{
    return m_long_opt == name;
}

inline bool libgetopt::option_base::matches(char short_opt) const
{
    return m_short_opt == short_opt;
}

inline bool libgetopt::option_base::has_long_option() const
{
    return m_long_opt != "" ;
}

inline bool libgetopt::option_base::has_short_option() const
{
    return m_short_opt != '\0';
}

inline const std::string& libgetopt::option_base::long_option() const
{
    return m_long_opt;
}

inline const char libgetopt::option_base::short_option() const
{
    return m_short_opt;
}

inline int libgetopt::option_base::val() const
{
    return m_val;
}

inline void libgetopt::option_base::set_val(const int val)
{
    m_val = val;
}

#endif
