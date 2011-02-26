#ifndef __CMDLINE_ARGS_H__
#define __CMDLINE_ARGS_H__

#include <vector>
#include <algorithm>

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
		void add(long long arg);
		void add(option_base* opt, char const * const arg);
		void add(option_base* opt, long long arg);

		operator char * const * ();

		int count() const;

		void clear();

	    private:

		static char* delchar(char*);
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
	    std::transform(m_args.begin(), m_args.end(), m_args.begin(), cmdline_args::delchar);
	    m_args.clear();
	}

	inline char* cmdline_args::delchar(char* arg)
	{
	    delete[] arg;
	    return NULL;
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
    }
}

#endif
