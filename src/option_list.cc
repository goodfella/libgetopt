#include <cassert>

#include <string>

#include "option_base.h"
#include "option_list.h"
#include "libgetopt_limits.h"

using namespace libgetopt;
using std::string;

char const * option_list::create_option_name(const parameter_name& name)
{
    assert(name.has_long_name() == true);

    string long_name = name.long_name();

    char * cname = new char[long_name.length() + 1];
    long_name.copy(cname, long_name.length());
    cname[long_name.length()] = '\0';

    return cname;
}

int option_list::add_option(option_base const * const opt)
{
    ::option getopt_opt;

    getopt_opt.name = create_option_name(opt->name());

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
    return getopt_opt.val;
}
