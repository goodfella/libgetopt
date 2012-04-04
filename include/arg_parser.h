#ifndef __ARG_PARSER_H__
#define __ARG_PARSER_H__

#include <string>
#include "named_parameter.h"

namespace libgetopt
{
    /** Parses an argument
     *
     *  Defines the common methods and data for a parameter class that
     *  takes and argument.
     */
    class arg_parser: public named_parameter
    {
	public:

	enum arg_policy_t
	{
	    no_arg,
	    arg_required,
	    arg_optional,
	};

	arg_parser(const std::string& long_name, const char short_name,
		   const arg_parser::arg_policy_t arg_policy);

	arg_parser(const std::string& long_name,
		   const arg_parser::arg_policy_t arg_policy);

	arg_parser(const char short_name,
		   const arg_parser::arg_policy_t arg_policy);

	    virtual ~arg_parser();

	/// Returns the arg setting
	const arg_parser::arg_policy_t arg_policy() const;

	    /** Returns whether the argument parsed is valid
	     *
	     *  @return true if the argument parsed with parse_arg()
	     *  was valid, false if no argument has been parsed with
	     *  parse_arg() or if the argument parsed with
	     *  parse_arg() was invalid
	     */
	    const bool arg_valid() const;

	    /** Returns whether an argument is present
	     *
	     *  @return true if an argument was parsed with
	     *  parse_arg(), false otherwise
	     */
	    const bool arg_present() const;

	    /** Parses an argument
	     *
	     *  Sets m_arg_valid, and m_arg_present accordingly and
	     *  parses the argument with __parse_arg().
	     *
	     *  @param arg Argument to parse
	     *
	     *  @param error Error string that is returned from
	     *  __parse_arg()
	     */
	    const bool parse_arg(char const * const arg,
				 std::string * const error);

	protected:

	    /* Sets the present and valid flags
	     *
	     *  Sets the arg_present flag to true and the arg_valid
	     *  flag to true.
	     *
	     */
	    void set_arg_present_valid();

	    /* Sets the present and valid flags
	     *
	     *  Sets the arg_present flag to true and the arg_valid
	     *  flag to false.
	     *
	     */
	    void set_arg_present_invalid();

	    /// Sets the arg_present and arg_valid flags to false
	    void clear_arg_present();

	    /** Parses an argument
	     *
	     *  This function is to be defined by the child class.  It
	     *  is called in parse_arg() to do the actual argument
	     *  parsing.
	     *
	     *  @param arg Argument to parse
	     *
	     *  @param error Error string that describes why the
	     *  parsing failed
	     *
	     *  @return true if parsing succeeded, false otherwise
	     */
	    virtual const bool derived_parse_arg(char const * const arg,
						 std::string * const error) = 0;

	private:

	    void set_arg_present(bool is_present);
	    void set_arg_valid(bool is_valid);

	    bool m_arg_valid;
	    bool m_arg_present;
	arg_policy_t m_arg_policy;
    };

    inline arg_parser::arg_parser(const std::string& long_name,
				  const char short_name,
				  const arg_parser::arg_policy_t arg_policy):
	named_parameter(long_name, short_name),
	m_arg_valid(false),
	m_arg_present(false),
	m_arg_policy(arg_policy)
    {}

    inline arg_parser::arg_parser(const std::string& long_name, 
				  const arg_parser::arg_policy_t arg_policy):
	named_parameter(long_name),
	m_arg_valid(false),
	m_arg_present(false),
	m_arg_policy(arg_policy)
    {}

    inline arg_parser::arg_parser(const char short_name,
				  const arg_parser::arg_policy_t arg_policy):
	named_parameter(short_name),
	m_arg_valid(false),
	m_arg_present(false),
	m_arg_policy(arg_policy)
    {}

    inline const bool arg_parser::arg_valid() const
    {
	return m_arg_valid;
    }

    inline const bool arg_parser::arg_present() const
    {
	return m_arg_present;
    }

    inline const arg_parser::arg_policy_t arg_parser::arg_policy() const
    {
	return m_arg_policy;
    }

    inline void arg_parser::set_arg_present(bool is_present)
    {
	m_arg_present = is_present;
    }

    inline void arg_parser::set_arg_valid(bool is_valid)
    {
	m_arg_valid = is_valid;
    }

    inline void arg_parser::set_arg_present_valid()
    {
	set_arg_present(true);
	set_arg_valid(true);
    }

    inline void arg_parser::set_arg_present_invalid()
    {
	set_arg_present(true);
	set_arg_valid(false);
    }

    inline void arg_parser::clear_arg_present()
    {
	set_arg_present(false);
	set_arg_valid(false);
    }
}

#endif
