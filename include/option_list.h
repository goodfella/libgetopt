#ifndef __OPTION_LIST_H__
#define __OPTION_LIST_H__

#include <vector>
#include <getopt.h>

#include "parameter_name.h"

namespace libgetopt
{
    class option_base;

    class option_list
    {
	public:

	    option_list(size_t reserve_size);

	    ~option_list();

	    int add_option(option_base const * const opt);
	    void add_option(::option opt);

	    operator const struct option*();

	    ::option& operator[] (size_t n);
	    const ::option& operator[] (size_t n) const;

	private:

	    char const * create_option_name(const parameter_name& name);
	    static void destroy_option_name(::option);

	    std::vector< ::option > m_options;
    };

    inline option_list::option_list(size_t reserve_size)
    {
	m_options.reserve(reserve_size);
    }

    inline option_list::~option_list()
    {
	for_each(m_options.begin(), m_options.end(),
		 option_list::destroy_option_name);
    }

    inline void option_list::destroy_option_name(::option opt)
    {
	delete[] opt.name;
    }

    inline void option_list::add_option(::option opt)
    {
	m_options.push_back(opt);
    }

    inline option_list::operator const struct option*()
    {
	return &m_options[0];
    }

    inline ::option& option_list::operator[] (size_t n)
    {
	return m_options[n];
    }

    inline const ::option& option_list::operator[] (size_t n) const
    {
	return (*this)[n];
    }
}

#endif
