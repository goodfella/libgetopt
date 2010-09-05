#ifndef __CMDLINE_PARSER_H__
#define __CMDLINE_PARSER_H__

#include <vector>

#include "arg_option.h"

namespace libgetopt
{
    typedef std::vector<option_base*> option_list_t;
    typedef std::vector<arg_option*> arg_option_list_t;

    class cmdline_parser
    {
	public:

	    void add_option(arg_option* arg_opt);
	    void parse(int argc, char* const argv[]);

	    void clear();

	private:

	    arg_option_list_t m_arg_options;
	    option_list_t m_options;
    };

    inline void cmdline_parser::add_option(arg_option* opt)
    {
	m_options.push_back(opt);
	m_arg_options.push_back(opt);
    }

    inline void cmdline_parser::clear()
    {
	m_options.clear();
	m_arg_options.clear();
    }
}

#endif
