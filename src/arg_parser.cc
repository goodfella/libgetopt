#include "arg_parser.h"
using namespace libgetopt;

arg_parser::~arg_parser() {}

const bool arg_parser::parse_arg(char const * const arg,
				 std::string * const error)
{
    set_arg_present(true);
    set_arg_valid(__parse_arg(arg, error));
    return arg_valid();
}
