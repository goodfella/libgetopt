#ifndef __GETOPT_OPTION_H__
#define __GETOPT_OPTION_H__

#include <cassert>
#include <getopt.h>
#include <string>

#include "option_base.h"


namespace libgetopt
{
    class getopt_option
    {
	public:

	    getopt_option(option_base*);

	    const ::option& option() const;

	    const std::string& optstring() const;

	private:

	    std::string m_optstring;
	    ::option m_opt;
    };

    inline getopt_option::getopt_option(option_base* opt_base)

    {
	// must either have a short option or a long option
	assert((opt_base->has_long_option() == true ||
		opt_base->has_short_option() == true));

	m_opt.name = NULL;
	m_opt.flag = NULL;

	if( opt_base->has_long_option() == true )
	{
	    m_opt.name = opt_base->long_option.c_str();
	    m_opt.flag = opt_base->flag_ptr();
	    m_opt.val = opt_base->val();
	    m_opt.has_arg = opt_base->arg_policy();
	}

	if( opt_base->has_short_option() == true )
	{
	    m_optstring = opt_base->short_option;
	    m_optstring += ':';
	}
    }

    inline const ::option& getopt_option::option() const
    {
	assert(m_opt.name != NULL);
	return m_opt;
    }

    inline const std::string& getopt_option::optstring() const
    {
	assert(m_optstring != "");
	return m_optstring;
    }
}

#endif
