#ifndef __OPTION_H__
#define __OPTION_H__

#include <string>

// forward declaration so we don't have to include
struct option;

namespace libgetopt
{
    class option
    {
	public:

	    option(char short_char, bool use_flag);
	    option(const std::string name, int val, bool use_flag);
	    option(const std::string name, int val, char short_char, bool use_flag);

	    bool is_set() const;
	    bool matches(int check_val) const;
	    bool use_flag() const;

	    int get_flag() const;


	protected:

	    int m_val;
	    std::string m_name;
	    char m_short;
	    bool m_use_flag;
	    int m_flag;
	    bool m_is_set;

	    virtual struct ::option* get_option();
	    virtual const std::string get_optstring() const;

	private:

	    void set_defaults();
    };
}

inline libgetopt::option::option(char short_char, bool use_flag):
    m_val(short_char),
    m_name(""),
    m_short(short_char),
    m_use_flag(use_flag)
{
    set_defaults();
}

inline libgetopt::option::option(const std::string name, int val, bool use_flag):
    m_val(val),
    m_name(name),
    m_short('\0'),
    m_use_flag(use_flag)
{
    set_defaults();
}

inline libgetopt::option::option(const std::string name, int val, char short_char,
				 bool use_flag):
    m_val(val),
    m_name(name),
    m_short(short_char),
    m_use_flag(use_flag)
{
    set_defaults();
}

inline void libgetopt::option::set_defaults()
{
    m_flag = 0;
    m_is_set = false;
}

inline bool libgetopt::option::is_set() const
{ return m_is_set; }


inline bool libgetopt::option::matches(int val) const
{
    int short_char = m_short;

    if( val == m_val || val == short_char )
    {
	return true;
    }
    else
    {
	return false;
    }
}

inline bool libgetopt::option::use_flag() const
{ return m_use_flag; }


inline int libgetopt::option::get_flag() const
{ return m_flag; }


#endif
