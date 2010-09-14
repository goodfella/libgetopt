#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <string>

#include "libgetopt.h"
#include "cmdline_args.h"

namespace libgetopt
{
    namespace unit_tests
    {
	class unit_test
	{
	    public:

		unit_test(const std::string& name,
			  int argc,
			  char * const * argv,
			  const cmdline_parser& parser,
			  cmdline_parser::parse_result::result_t expected_result);

		bool run();

		const std::string name;

	    private:

		int m_argc;
		char * const * m_argv;
		const cmdline_parser& m_parser;
		cmdline_parser::parse_result::result_t m_exp_res;
	};

	inline unit_test::unit_test(const std::string& n,
				    int argc,
				    char * const * argv,
				    const cmdline_parser& parser,
				    cmdline_parser::parse_result::result_t expected_result):
	    name(n),
	    m_argc(argc),
	    m_argv(argv),
	    m_parser(parser),
	    m_exp_res(expected_result)
	{}
    }
}

#endif
