#include "arg_option.h"

using namespace libgetopt;

arg_option::~arg_option(){}

argument_policy_t arg_option::arg_policy() const
{
    return arg_policy_required;
}

bool arg_option::set(char const * const optarg)
{
    present();

    bool ret = true;

    if( optarg != NULL )
    {
	ret = m_valid_arg = parse_arg(optarg);
    }

    return ret;
}
