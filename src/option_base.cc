#include <stdexcept>
#include <string>

#include "option_base.h"
#include "ioption_base_visitor.h"

using namespace libgetopt;
using std::logic_error;
using std::string;

option_base::~option_base() {}

void option_base::present(const bool is_present)
{
    if( arg_required() == true && is_present == true )
    {
	throw logic_error("present can't be set without an arg");
    }

    set_present_no_throw(is_present);
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

void option_base::visit(const std::string& arg)
{
    if( m_base_visitor != NULL )
    {
	m_base_visitor->visit(*this, arg);
    }

    derived_visit(arg);
}
