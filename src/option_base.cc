#include <getopt.h>
#include "option.h"

using std::string;

struct ::option* libgetopt::option::get_option()
{
    struct ::option* opt = NULL;

    if( m_name != "" )
    {
	char* name = new char[m_name.size() + 1];
	m_name.copy(name, m_name.size());
	name[m_name.size() - 1] = '\0';

	opt = new ::option();

	opt->name = name;
	opt->flag = &m_flag;
	opt->val = m_val;
    }
    else
    {
	opt = NULL;
    }

    return opt;
}

const string libgetopt::option::get_optstring() const
{
    string optstring = "";

    if( m_short != '\0' )
    {
	optstring = m_short;
    }

    return optstring;
}


