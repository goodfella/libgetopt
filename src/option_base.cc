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
    m_present = is_present;

    if( is_present == false )
    {
	arg_parser::clear_arg_present();
    }
    else
    {
	arg_parser::set_arg_present_valid();
    }
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

const bool option_base::name_match(option_base const * const lhs,
				   const string& rhs)
{
    if( lhs == NULL )
    {
	throw logic_error("lhs is NULL");
    }

    return lhs->name() == rhs;
}

void option_base::visit(const std::string& arg)
{
    if( m_base_visitor != NULL )
    {
	m_base_visitor->visit(*this, arg);
    }

    derived_visit(arg);
}

const bool option_base::derived_parse_arg(char const * const optarg,
					  std::string* const err_str)
{
    present(true);

    // derived class' parse arg
    bool ret = option_parse_arg(optarg, err_str);
    visit(optarg);

    return ret;
}
