#include <cassert>
#include <string>
#include <cstring>

#include "option_base.h"
#include "option_list.h"
#include "libgetopt_limits.h"

using namespace libgetopt;
using std::string;

char* option_list::create_option_name(const parameter_name& name)
{
    assert(name.has_long_name() == true);
    return duplicate_cstring(name.long_name().c_str());
}

int option_list::add_long_option(option_base const * const opt)
{
    ::option getopt_opt;

    auto_cstring_ptr long_name(create_option_name(opt->name()));
    getopt_opt.name = long_name.get();

    getopt_opt.has_arg = opt->arg_required() == true ? required_argument : optional_argument;

    getopt_opt.flag = NULL;

    if( opt->name().has_short_name() == false )
    {
	getopt_opt.val = m_options.size() + libgetopt::limits::max_short_options;
    }
    else
    {
	getopt_opt.val = opt->name().short_name();
    }

    m_options.push_back(getopt_opt);
    long_name.release();

    return getopt_opt.val;
}
