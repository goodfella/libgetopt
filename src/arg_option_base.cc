#include "arg_option_base.h"

using namespace libgetopt;

arg_option_base::~arg_option_base(){}

argument_policy_t arg_option_base::arg_policy() const
{
    return arg_policy_required;
}
