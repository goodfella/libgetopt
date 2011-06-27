#ifndef __ARG_PARSER_H__
#define __ARG_PARSER_H__

#include <string>

namespace libgetopt
{
    /** Parses an argument
     *
     *  Defines the common methods and data for a parameter class that
     *  takes and argument.
     */
    class arg_parser
    {
	public:

	    explicit arg_parser(const bool arg_required);

	    virtual ~arg_parser();

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

	    /** Returns whether an argument is required
	     *
	     *  @return true if an argument is required, false
	     *  otherwise
	     */
	    const bool arg_required() const;

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

	    /// Sets the are_present and arg_valid flags
	    void set_arg_flags(bool is_present, bool is_valid);

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
	    virtual const bool __parse_arg(char const * const arg,
					   std::string * const error) = 0;

	private:

	    bool m_arg_valid;
	    bool m_arg_present;
	    bool m_arg_required;
    };

    inline arg_parser::arg_parser(const bool arg_required):
	m_arg_valid(false),
	m_arg_present(false),
	m_arg_required(arg_required)
    {}

    inline const bool arg_parser::arg_valid() const
    {
	return m_arg_valid;
    }

    inline const bool arg_parser::arg_present() const
    {
	return m_arg_present;
    }

    inline const bool arg_parser::arg_required() const
    {
	return m_arg_required;
    }

    inline void arg_parser::set_arg_flags(bool is_present, bool is_valid)
    {
	m_arg_present = is_present;

	if( is_present == false )
	{
	    is_valid = false;
	}

	m_arg_valid = is_valid;
    }
}

#endif