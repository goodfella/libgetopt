#ifndef __PARSE_RESULT_H__
#define __PARSE_RESULT_H__

namespace libgetopt
{
    struct parse_result
    {
	    enum result_t
	    {
		result_success,
		result_invalid_option,
		result_invalid_arg,
		result_missing_arg
	    };

	    parse_result();

	    explicit parse_result(const std::string& invalid_opt);

	    explicit parse_result(option_base* opt);

	    parse_result(option_base* opt, const std::string& bad_arg,
			 const std::string& err_str);

	    operator parse_result::result_t () const;

	    bool good() const;
	    bool bad() const;

	    result_t result;
	    std::string option_name;
	    std::string error_string;
	    std::string invalid_arg;
    };

    inline parse_result::parse_result(): result(result_success) {}

    inline parse_result::parse_result(const std::string& invalid_opt):
	result(result_invalid_option), option_name(invalid_opt)
    {}

    inline parse_result::parse_result(option_base* opt):
	result(result_missing_arg),
	option_name(opt->name.string_name())
    {}

    inline parse_result::parse_result(option_base* opt,
				      const std::string& bad_arg,
				      const std::string& err_str):
	result(result_invalid_arg),
	option_name(opt->name.string_name()),
	error_string(err_str),
	invalid_arg(bad_arg)
    {}

    inline parse_result::operator result_t () const { return result; }

    inline bool parse_result::good() const {return result == result_success;}

    inline bool parse_result::bad() const {return result != result_success;}
}

#endif
