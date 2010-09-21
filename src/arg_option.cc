#include <string>
#include "arg_option.h"
#include "getopt_option.h"

using namespace libgetopt;
using std::string;

arg_option::~arg_option(){}

bool arg_option::parse_arg(char const * const optarg, string* err_str)
{
    present();

    bool ret = true;

    if( optarg != NULL )
    {
	ret = m_valid_arg = parse(optarg, err_str);
    }

    return ret;
}

void arg_option::fill_option(getopt_option* opt) const
{
    option_base::fill_option(opt);

    argument_policy_t has_arg = arg_policy();
    opt->has_arg = has_arg;

    if( opt->optstring != "" )
    {
	if( has_arg == arg_policy_required )
	{
	    opt->optstring += ':';
	}
	else if( has_arg == arg_policy_optional )
	{
	    opt->optstring += "::";
	}
    }
}
