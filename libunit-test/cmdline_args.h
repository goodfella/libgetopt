#ifndef __CMDLINE_ARGS_H__
#define __CMDLINE_ARGS_H__

#include <vector>
#include <algorithm>
#include <string>

#include "libgetopt_string.h"

namespace libgetopt
{
    class option_base;

    namespace unit_tests
    {
	class cmdline_args
	{
	    public:

		cmdline_args(char const * const arg0);
		cmdline_args();

		~cmdline_args();

		void add(char const * const option);
		void add(char const * const option, char const * const arg);
		void add(char const * const option, long long arg);
		void add(option_base* opt);
		void add(option_base* opt, const std::string&);
		void add(long long arg);
		void add(option_base* opt, char const * const arg);
		void add(option_base* opt, long long arg);

		operator char * const * ();

		int count() const;

		void clear();

	    private:

		std::vector<char*> m_args;
	};

	inline cmdline_args::cmdline_args(){}

	inline cmdline_args::cmdline_args(char const * const arg0)
	{
	    add(arg0);
	}

	inline cmdline_args::~cmdline_args()
	{
	    clear();
	}

	inline void cmdline_args::clear()
	{
	    std::transform(m_args.begin(), m_args.end(), m_args.begin(), delete_cstring);
	    m_args.clear();
	}

	inline int cmdline_args::count() const
	{
	    // if the null pointer has been appended then don't
	    // include that in the count
	    if( m_args.back() == NULL )
	    {
		return m_args.size() - 1;
	    }
	    else
	    {
		return m_args.size();
	    }
	}

	inline void cmdline_args::add(option_base* opt, const std::string& arg)
	{
	    add(opt, arg.c_str());
	}
    }
}

#endif
