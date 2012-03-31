#ifndef __CMDLINE_TOKEN_H__
#define __CMDLINE_TOKEN_H__

#include <string>

namespace libgetopt
{
    class cmdline_token
    {
	public:

	enum token_type_t
	{
	    unknown,
	    long_named,
	    short_named,
	    unnamed
	};

	cmdline_token();

	const bool has_arg() const;
	const bool is_named() const;
	const bool is_unnamed() const;

	const std::string& parameter() const;
	const std::string& name() const;
	const std::string& arg() const;
	const token_type_t type() const;

	std::string& parameter();
	std::string& name();
	std::string& arg();
	token_type_t& type();

	void parameter(const std::string& param);
	void name(const std::string& name);
	void arg(const std::string& arg);
	void type(const token_type_t type);

	private:

	std::string m_parameter;
	std::string m_name;
	std::string m_arg;
	token_type_t m_type;
    };

    inline cmdline_token::cmdline_token():
	m_parameter(""),
	m_name(""),
	m_arg("")
    {}

    inline const bool cmdline_token::has_arg() const
    {
	return arg() != "";
    }

    inline const bool cmdline_token::is_named() const
    {
	return ( (type() == cmdline_token::long_named) ||
		 (type() == cmdline_token::short_named) );
    }

    inline const bool cmdline_token::is_unnamed() const
    {
	return type() == cmdline_token::unnamed;
    }

    inline const std::string& cmdline_token::parameter() const
    {
	return m_parameter;
    }

    inline const std::string& cmdline_token::name() const
    {
	return m_name;
    }

    inline const std::string& cmdline_token::arg() const
    {
	return m_arg;
    }

    inline const cmdline_token::token_type_t cmdline_token::type() const
    {
	return m_type;
    }

    inline std::string& cmdline_token::parameter()
    {
	return m_parameter;
    }

    inline std::string& cmdline_token::name()
    {
	return m_name;
    }

    inline std::string& cmdline_token::arg()
    {
	return m_arg;
    }

    inline cmdline_token::token_type_t& cmdline_token::type()
    {
	return m_type;
    }

    inline void cmdline_token::parameter(const std::string& new_param)
    {
	parameter() = new_param;
    }

    inline void cmdline_token::name(const std::string& new_name)
    {
	name() = new_name;
    }

    inline void cmdline_token::arg(const std::string& new_arg)
    {
	arg() = new_arg;
    }

    inline void cmdline_token::type(const token_type_t new_type)
    {
	type() = new_type;
    }
}

#endif
