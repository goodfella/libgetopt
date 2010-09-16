#ifndef __OPTION_BASE_H__
#define __OPTION_BASE_H__

#include <cctype>
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

	    invalid_option(const std::string& err):
		std::logic_error(err)
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
	    typedef bool (option_base::*duplicate_opt_predicate_t)(option_base const * const) const;

	    static const short_opt_predicate_t short_opt_matches;
	    static const long_opt_predicate_t long_opt_matches;
	    static const val_predicate_t val_matches;
	    static const duplicate_opt_predicate_t option_base_matches;;

	    static bool bad_char(const char chr);

	    explicit option_base(const char short_opt);
	    option_base(const std::string& long_opt, const int val);
	    option_base(const std::string& long_opt, const char opt);

	    virtual ~option_base();

	    bool matches(int check_val) const;
	    bool matches(char const * name) const;
	    bool matches(char short_opt) const;
	    bool matches(option_base const * const opt_base) const;

	    bool has_long_option() const;
	    bool has_short_option() const;

	    const std::string full_long_option() const;
	    const std::string full_short_option() const;

	    const std::string name() const;
	    const std::string full_name() const;

	    int val() const;

	    virtual argument_policy_t arg_policy() const = 0;

	    const char short_option;
	    const std::string long_option;


	protected:

	    virtual int* flag_ptr();
	    void val(const int val);

	private:

	    // no copying allowed
	    option_base(const option_base& opt);
	    option_base& operator = (const option_base& opt);

	    static void check_opt(const char short_opt);
	    static void check_opt(const std::string& long_opt);

	    int m_val;
    };
}

inline bool libgetopt::option_base::bad_char(const char chr)
{
    return ! isgraph(chr);
}

inline libgetopt::option_base::option_base(const char short_opt):
    short_option(short_opt),
    long_option(""),
    m_val(short_opt)
{
    check_opt(short_opt);
}

inline libgetopt::option_base::option_base(const std::string& long_opt, int val):
    short_option('\0'),
    long_option(long_opt),
    m_val(val)
{
    check_opt(long_opt);
}

inline libgetopt::option_base::option_base(const std::string& long_opt, const char short_opt):
    short_option(short_opt),
    long_option(long_opt),
    m_val(short_opt)
{
    check_opt(long_opt);
    check_opt(short_opt);
}

inline bool libgetopt::option_base::matches(int val) const
{
    return val == m_val;
}

inline bool libgetopt::option_base::matches(char const * name) const
{
    return long_option == name;
}

inline bool libgetopt::option_base::matches(char short_opt) const
{
    return short_option == short_opt;
}

inline bool libgetopt::option_base::has_long_option() const
{
    return long_option != "" ;
}

inline bool libgetopt::option_base::has_short_option() const
{
    return short_option != '\0';
}

inline const std::string libgetopt::option_base::full_long_option() const
{
    return "--" + long_option;
}

inline const std::string libgetopt::option_base::full_short_option() const
{
    std::string opt;

    opt += "-";
    opt += short_option;
    return opt;
}

inline int libgetopt::option_base::val() const
{
    return m_val;
}

inline void libgetopt::option_base::val(const int val)
{
    m_val = val;
}

#endif
