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
	    option_base(const std::string& name, int val);
	    option_base(const std::string& name, char opt);

	    virtual ~option_base(){}

	    virtual bool is_set() const;
	    bool matches(int check_val) const;

	protected:

	    virtual struct ::option* get_option();
	    virtual const std::string get_optstring() const;
	    void set();

	private:

	    char m_opt;
	    std::string m_name;
	    int m_val;
	    bool m_is_set;
    };
}

inline libgetopt::option_base::option_base(char opt):
    m_opt(opt),
    m_name(""),
    m_val(0),
    m_is_set(false)
{}

inline libgetopt::option_base::option_base(const std::string& name, int val):
    m_opt('\0'),
    m_name(name),
    m_val(val),
    m_is_set(false)
{}

inline libgetopt::option_base::option_base(const std::string& name, char opt):
    m_opt(opt),
    m_name(name),
    m_val(opt),
    m_is_set(false)
{}

inline bool libgetopt::option_base::is_set() const
{
    return m_is_set;
}


inline bool libgetopt::option_base::matches(int val) const
{
    int opt = m_opt;

    if( val == opt )
    {
	return true;
    }
    else
    {
	return false;
    }
}


inline void libgetopt::option_base::set()
{ m_is_set = true; }


#endif
