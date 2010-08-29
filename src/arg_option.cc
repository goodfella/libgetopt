#include <getopt.h>
#include "arg_option.h"

using namespace libgetopt;
using std::string;

const string arg_option::get_optstring() const
{
    string optstring = option_base::get_optstring();

    if( optstring != "" )
    {
	optstring += ':';
    }

    return optstring;
}

struct option* arg_option::get_option()
{
    struct ::option* opt = option_base::get_option();

    opt->has_arg = required_argument;

    return opt;
}
