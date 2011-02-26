#include "arg_parser.h"
using namespace libgetopt;

arg_parser::~arg_parser() {}

const bool arg_parser::parse_arg(char const * const arg,
				 std::string * const error)
{
    m_arg_present = true;
    return m_arg_valid = __parse_arg(arg, error);
}
