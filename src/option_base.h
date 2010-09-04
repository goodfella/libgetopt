#ifndef __OPTION_BASE_H__
#define __OPTION_BASE_H__

#include <cassert>
#include <string>

namespace libgetopt
{
    enum argument_policy_t
    {
	arg_policy_none,
	arg_policy_required,
	arg_policy_optional
    };

    class option_base
    {
	    friend class getopt_option;

	public:

	    explicit option_base(char short_opt);
	    option_base(const std::string& long_opt, int val);
	    option_base(const std::string& long_opt, char opt);

	    virtual ~option_base();

	    void set();
	    virtual bool is_set() const;
	    bool matches(int check_val) const;
	    bool has_long_option() const;
	    bool has_short_option() const;

	    const std::string& long_option() const;
	    const char short_option() const;
	    int val() const;

	    virtual argument_policy_t arg_policy() const = 0;

	protected:

	    virtual int* flag_ptr();

	private:

	    const char m_short_opt;
	    const std::string m_long_opt;
	    const int m_val;
	    bool m_is_set;
    };
}

inline libgetopt::option_base::option_base(char short_opt):
    m_short_opt(short_opt),
    m_long_opt(""),
    m_val(short_opt),
    m_is_set(false)
{
    assert(short_opt != '\0');
}

inline libgetopt::option_base::option_base(const std::string& long_opt, int val):
    m_short_opt('\0'),
    m_long_opt(long_opt),
    m_val(val),
    m_is_set(false)
{
    assert(long_opt != "");
}

inline libgetopt::option_base::option_base(const std::string& long_opt, char short_opt):
    m_short_opt(short_opt),
    m_long_opt(long_opt),
    m_val(short_opt),
    m_is_set(false)
{
    assert(long_opt != "");
    assert(short_opt != '\0');
}

inline bool libgetopt::option_base::matches(int val) const
{
    if( val == m_val )
    {
	return true;
    }
    else
    {
	return false;
    }
}

inline bool libgetopt::option_base::has_long_option() const
{
    return ( m_long_opt != "" );
}

inline bool libgetopt::option_base::has_short_option() const
{
    return ( m_short_opt != '\0' );
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


inline void libgetopt::option_base::set()
{ m_is_set = true; }


#endif
