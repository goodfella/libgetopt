#include "arg_option_base.h"

using namespace libgetopt;

arg_option_base::~arg_option_base(){}

argument_policy_t arg_option_base::arg_policy() const
{
    return arg_policy_required;
}

bool arg_option_base::set(char const * const optarg)
{
    present();

    if( optarg != NULL )
    {
	m_valid_arg = parse_arg(optarg);
    }

    return m_valid_arg;
}
