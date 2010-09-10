#ifndef __CMDLINE_PARSER_H__
#define __CMDLINE_PARSER_H__

#include <vector>
#include <stdexcept>
#include <string>

#include "arg_option.h"

namespace libgetopt
{
    typedef std::vector<option_base*> option_list_t;
    typedef std::vector<arg_option*> arg_option_list_t;

    class duplicate_option : public std::logic_error
    {
	public:

	    explicit duplicate_option(const std::string& option_name):
		logic_error("duplicate option: " + option_name)
	    {}
    };

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

		    parse_result(const std::string& invalid_opt):
			error_option(NULL),
			result(result_invalid_option),
			error_string("invalid option"),
			invalid_option(invalid_opt)
		    {}

		    parse_result(arg_option* opt):
			error_option(opt),
			result(result_missing_arg),
			error_string("missing arg")
		    {}


		    parse_result(arg_option* opt,
				 const std::string& bad_arg,
				 const std::string& err_str):
			error_option(opt),
			result(result_invalid_arg),
			error_string(err_str),
			invalid_option(""),
			invalid_arg(bad_arg)
		    {}

		    operator result_t () { return result; }

		    bool good() const {return result == result_success;}
		    bool bad() const {return result != result_success;}

		    arg_option* error_option;
		    result_t result;
		    std::string error_string;
		    std::string invalid_option;
		    std::string invalid_arg;
	    };

	    cmdline_parser() {}

	    void add_option(arg_option* arg_opt);
	    parse_result parse(int argc, char* const argv[]);

	    void clear();

	private:

	    // no copying allowed
	    cmdline_parser(const cmdline_parser&);
	    cmdline_parser& operator = (const cmdline_parser&);

	    template<class List_Type>
	    static option_base* find_option(option_base const * const opt,
					    const List_Type& options);

	    void add_option(option_base* opt);

	    arg_option_list_t m_arg_options;
	    option_list_t m_options;
    };

    inline void cmdline_parser::clear()
    {
	m_options.clear();
	m_arg_options.clear();
    }

    template<class List_Type>
    option_base* cmdline_parser::find_option(option_base const * const opt,
					     const List_Type& options)
    {
	typename List_Type::const_iterator option =
	    find_if(options.begin(), options.end(),
		    std::bind2nd(std::mem_fun(option_base::duplicate_opt_pred), opt));

	if( option != options.end() )
	{
	    return *option;
	}

	return NULL;
    }
}

#endif
