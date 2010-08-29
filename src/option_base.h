#ifndef __OPTION_BASE_H__
#define __OPTION_BASE_H__

#include <string>

// forward declaration so we don't have to include
struct option;

namespace libgetopt
{
    class option_base
    {
	public:

	    option_base(char opt);
	    option_base(const std::string name, int val, bool use_flag);
	    option_base(const std::string name, char opt);

	    virtual ~option_base(){}

	    bool is_set() const;
	    bool matches(int check_val) const;
	    bool use_flag() const;

	    int get_flag() const;

	protected:

	    virtual struct ::option* get_option();
	    virtual const std::string get_optstring() const;
	    void set();

	private:

	    int m_val;
	    std::string m_name;
	    char m_opt;
	    bool m_use_flag;
	    int m_flag;
	    bool m_is_set;

	    void set_defaults();
    };
}

inline libgetopt::option_base::option_base(char opt):
    m_val(0),
    m_name(""),
    m_opt(opt),
    m_use_flag(false)
{
    set_defaults();
}

inline libgetopt::option_base::option_base(const std::string name, int val, bool use_flag):
    m_val(val),
    m_name(name),
    m_opt('\0'),
    m_use_flag(use_flag)
{
    set_defaults();
}

inline libgetopt::option_base::option_base(const std::string name, char opt):
    m_val(opt),
    m_name(name),
    m_opt(opt),
    m_use_flag(false)
{
    set_defaults();
}

inline void libgetopt::option_base::set_defaults()
{
    m_flag = ~m_val;
    m_is_set = false;
}

inline bool libgetopt::option_base::is_set() const
{
    if( m_val == m_flag )
    {
	return true;
    }
    else
    {
	return m_is_set;
    }
}


inline bool libgetopt::option_base::matches(int val) const
{
    int opt = m_opt;

    if( val == m_val || val == opt )
    {
	return true;
    }
    else
    {
	return false;
    }
}


inline bool libgetopt::option_base::use_flag() const
{ return m_use_flag; }


inline int libgetopt::option_base::get_flag() const
{ return m_flag; }

inline void libgetopt::option_base::set()
{ m_is_set = true; }

#endif
