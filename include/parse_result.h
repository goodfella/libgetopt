#ifndef __PARSE_RESULT_H__
#define __PARSE_RESULT_H__

namespace libgetopt
{
    class parse_result
    {
	public:

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

	    bool good() const;
	    bool bad() const;

	    result_t result() const;
	    const std::string& option_name() const;
	    const std::string& error_string() const;
	    const std::string& invalid_arg() const;

	private:

	    result_t m_result;
	    std::string m_option_name;
	    std::string m_error_string;
	    std::string m_invalid_arg;
    };

    inline parse_result::parse_result(): m_result(result_success) {}

    inline parse_result::parse_result(const std::string& invalid_opt):
	m_result(result_invalid_option),
	m_option_name(invalid_opt)
    {}

    inline parse_result::parse_result(option_base* opt):
	m_result(result_missing_arg),
	m_option_name(opt->name().string_name())
    {}

    inline parse_result::parse_result(option_base* opt,
				      const std::string& bad_arg,
				      const std::string& err_str):
	m_result(result_invalid_arg),
	m_option_name(opt->name().string_name()),
	m_error_string(err_str),
	m_invalid_arg(bad_arg)
    {}

    inline bool parse_result::good() const {return result() == result_success;}
    inline bool parse_result::bad() const {return !good();}

    inline parse_result::result_t parse_result::result() const
    {
	return m_result;
    }

    inline const std::string& parse_result::option_name() const
    {
	return m_option_name;
    }

    inline const std::string& parse_result::error_string() const
    {
	return m_error_string;
    }

    inline const std::string& parse_result::invalid_arg() const
    {
	return m_invalid_arg;
    }
}

#endif
