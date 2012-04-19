#include <sstream>
#include <string>
#include <cstring>
#include <ostream>
#include "libgetopt_string.h"
#include "cmdline_args.h"

#include "option_base.h"

using namespace libgetopt::unit_tests;
using std::string;
using std::stringstream;
using std::ostream;
using std::vector;

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

void cmdline_args::generate_named_param(const string& name,
					const string& arg,
					string& param)
{
    generate_named_param(name, param);

    if( name.length() > 1 )
    {
	param += '=';
    }

    param += arg;
}

void cmdline_args::generate_named_param(const string& name,
					string& param)
{
    if( name.length() == 1 )
    {
	generate_named_param(name[0], param);
    }
    else
    {
	param += "--" + name;
    }
}

void cmdline_args::generate_named_param(const char name, string& param)
{
    param += '-';
    param += name;
}

void cmdline_args::generate_named_param(const char name, const string& arg,
					string& param)
{
    generate_named_param(name, param);
    param += arg;
}

namespace libgetopt
{
    namespace unit_tests
    {
	std::ostream& operator <<(std::ostream& stream, const cmdline_args& args)
	{
	    for(vector<char*>::const_iterator i = args.m_args.begin(); i != args.m_args.end(); ++i)
	    {
		if( *i != NULL )
		{
		    stream << *i << ' ';
		}
	    }

	    return stream;
	}
    }
}
