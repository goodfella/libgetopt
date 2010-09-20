#include <string>
#include "arg_option.h"
#include "getopt_option.h"

using namespace libgetopt;
using std::string;

arg_option::~arg_option(){}

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

void arg_option::fill_option(getopt_option* opt) const
{
    option_base::fill_option(opt);
    opt->opt.has_arg = arg_policy();
    opt->optstring += ':';
}
