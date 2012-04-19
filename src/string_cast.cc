#include "string_cast.h"

using namespace std;

namespace libgetopt
{
    template<>
    const bool string_equals(parse_arg_passed const * const type, const std::string& str)
    {
	return type->arg == str;
    }

    template<>
    const bool string_equals(parse_arg_failed const * const type, const std::string& str)
    {
	return type->arg == str;
    }
}
