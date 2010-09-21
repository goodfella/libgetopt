#ifndef __OPTION_BASE_H__
#define __OPTION_BASE_H__

#include <cctype>
#include <string>
#include <stdexcept>


namespace libgetopt
{
    class invalid_option: public std::logic_error
    {
	public:

	    invalid_option(const std::string& err):
		std::logic_error(err)
	    {}
    };

    struct getopt_option;

    class option_base
    {
	    friend class cmdline_parser;

	public:

	    typedef bool (option_base::*val_predicate_t)(const int) const;
	    typedef bool (option_base::*long_opt_predicate_t)(char const * const) const;
	    typedef bool (option_base::*short_opt_predicate_t)(const char) const;
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

	    bool matches(const int check_val) const;
	    bool matches(char const * const name) const;
	    bool matches(const char short_opt) const;
	    bool matches(option_base const * const opt_base) const;

	    bool has_long_option() const;
	    bool has_short_option() const;

	    const std::string long_option() const;
	    const char short_option() const;

	    const std::string full_long_option() const;
	    const std::string full_short_option() const;

	    const std::string name() const;
	    const std::string full_name() const;

	    int val() const;

	protected:

	    virtual void fill_option(getopt_option* opt) const = 0;


	private:

	    // no copying allowed
	    option_base(const option_base& opt);
	    option_base& operator = (const option_base& opt);

	    static void check_opt(const char short_opt);
	    static void check_opt(const std::string& long_opt);
	    void val(const int val);

	    const char m_short_option;
	    const std::string m_long_option;
	    int m_val;
    };
}

inline bool libgetopt::option_base::bad_char(const char chr)
{
    return ! isgraph(chr);
}

inline libgetopt::option_base::option_base(const char short_opt):
    m_short_option(short_opt),
    m_long_option(""),
    m_val(short_opt)
{
    check_opt(short_opt);
}

inline libgetopt::option_base::option_base(const std::string& long_opt, int val):
    m_short_option('\0'),
    m_long_option(long_opt),
    m_val(val)
{
    check_opt(long_opt);
}

inline libgetopt::option_base::option_base(const std::string& long_opt, const char short_opt):
    m_short_option(short_opt),
    m_long_option(long_opt),
    m_val(short_opt)
{
    check_opt(long_opt);
    check_opt(short_opt);
}

inline bool libgetopt::option_base::matches(const int val) const
{
    return val == m_val;
}

inline bool libgetopt::option_base::matches(char const * const name) const
{
    return m_long_option == name;
}

inline bool libgetopt::option_base::matches(const char short_opt) const
{
    return m_short_option == short_opt;
}

inline bool libgetopt::option_base::has_long_option() const
{
    return m_long_option != "" ;
}

inline bool libgetopt::option_base::has_short_option() const
{
    return m_short_option != '\0';
}

inline const std::string libgetopt::option_base::long_option() const
{
    return m_long_option;
}

inline const char libgetopt::option_base::short_option() const
{
    return m_short_option;
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
