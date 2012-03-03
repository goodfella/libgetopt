#include <sstream>
#include <string>
#include <cstring>
#include "libgetopt_string.h"
#include "cmdline_args.h"

#include "option_base.h"

using namespace libgetopt::unit_tests;
using std::string;
using std::stringstream;

void cmdline_args::add(char const * const option)
{
    auto_cstring_ptr arg(duplicate_cstring(option));
    m_args.push_back(arg.get());
    arg.release();
}

void cmdline_args::add(char const * const option, char const * const arg)
{
    add(option);
    add(arg);
}

void cmdline_args::add(option_base* opt)
{
    string opt_name(1, '-');

    if( opt->name().has_long_name() )
    {
	opt_name += '-';
	opt_name += opt->name().long_name();
    }
    else
    {
	opt_name += opt->name().short_name();
    }

    add(opt_name.c_str());
}

void cmdline_args::add(long long arg)
{
    stringstream arg_ss;
    arg_ss << arg;
    string arg_str = arg_ss.str();

    add(arg_str.c_str());
}

void cmdline_args::add(option_base* opt, char const * const arg)
{
    add(opt);
    add(arg);
}

void cmdline_args::add(option_base* opt, long long arg)
{
    add(opt);
    add(arg);
}

void cmdline_args::add(char const * const option, long long arg)
{
    add(option);
    add(arg);
}

cmdline_args::operator char * const * ()
{
    if( m_args.size() == 0 || m_args.back() != NULL )
    {
	m_args.push_back(NULL);
    }

    return &m_args[0];
}

