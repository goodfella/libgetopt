#include <stdexcept>

#include "option_base.h"

using namespace libgetopt;
using std::logic_error;

void option_base::set_present(const bool is_present)
{
    if( arg_parser::arg_required() == true && is_present == true )
    {
	throw logic_error("present can't be set without an arg");
    }

    set_present_no_throw(is_present);
}

const bool option_base::is_present() const
{
    return m_present;
}

const bool option_base::ptr_match(option_base const * const lhs,
				  option_base const * const rhs)
{
    if( lhs == NULL || rhs == NULL )
    {
	throw logic_error("lhs or rhs is NULL");
    }

    return *lhs == *rhs;
}
