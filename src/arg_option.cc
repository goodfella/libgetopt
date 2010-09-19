#include <string>
#include "arg_option.h"

using namespace libgetopt;
using std::string;

arg_option::~arg_option(){}

argument_policy_t arg_option::arg_policy() const
{
    return arg_policy_required;
}

bool arg_option::parse_arg(char const * const optarg, string& err_str)
{
    present();

    bool ret = true;

    if( optarg != NULL )
    {
	ret = m_valid_arg = parse(optarg, err_str);
    }

    return ret;
}
