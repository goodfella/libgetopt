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

	    struct parse_result
	    {
		    enum result_t
		    {
			result_success,
			result_invalid_option,
			result_invalid_arg,
			result_missing_arg
		    };

		    parse_result(): error_option(NULL), result(result_success) {}

		    parse_result(arg_option* opt, result_t res):
			error_option(opt),
			result(res)
		    {}

		    operator result_t () { return result; }

		    bool good() const {return result == result_success;}
		    bool bad() const {return result != result_success;}

		    arg_option* error_option;
		    result_t result;
	    };

	    void add_option(arg_option* arg_opt);
	    parse_result parse(int argc, char* const argv[]);

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
