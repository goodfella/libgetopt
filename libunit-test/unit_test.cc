#include "unit_test.h"

using namespace libgetopt;
using namespace libgetopt::unit_tests;

bool unit_test::run()
{
    parse_result res = m_parser.parse(m_argc, m_argv);

    if( res.result() != m_exp_res )
    {
	return false;
    }

    return true;
}
