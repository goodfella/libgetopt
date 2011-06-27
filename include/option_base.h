#ifndef __OPTION_BASE_H__
#define __OPTION_BASE_H__

#include <string>

#include "parameter_name.h"
#include "arg_parser.h"
#include "iparameter.h"

namespace libgetopt
{
    /// Base class for the option classes
    class option_base: public iparameter, public arg_parser
    {
	public:

	    option_base(const std::string& long_name, const char short_name,
			const bool arg_required = true);

	    option_base(const std::string& long_name,
			const bool arg_required = true);

	    option_base(const char short_name, const bool arg_required = true);

	    /** Sets whether or not an option is present
	     *
	     *  @param is_present Present or not present
	     */
	    void set_present(const bool is_present);

	    /** Returns whether or not the option is present
	     *
	     *  @param is_present Value to set the present flag to
	     */
	    const bool is_present() const;

	    /** True if two option_base classes passed as pointers match
	     *
	     *  This function is to be used as a predicate in standard
	     *  algorithms for lists of optio_base pointers.
	     */
	    static const bool ptr_match(option_base const * const lhs,
					option_base const * const rhs);

	    parameter_name name;

	protected:

	    void set_present_no_throw(bool is_present);
	    void* m_arg;

	private:

	    // No copying
	    option_base(const option_base&);
	    option_base& operator=(const option_base&);

	    bool m_present;
    };

    inline option_base::option_base(const std::string& long_name,
				    const char short_name,
				    const bool arg_required):
	arg_parser(arg_required),
	name(long_name, short_name),
	m_arg(NULL),
	m_present(false)
    {}

    inline option_base::option_base(const std::string& long_name,
				    const bool arg_required):
	arg_parser(arg_required),
	name(long_name),
	m_arg(NULL),
	m_present(false)
    {}

    inline option_base::option_base(const char short_name,
				    const bool arg_required):
	arg_parser(arg_required),
	name(short_name),
	m_arg(NULL),
	m_present(false)
    {}

    inline void option_base::set_present_no_throw(bool is_present)
    {
	m_present = is_present;

	if( is_present == false )
	{
	    arg_parser::set_arg_flags(false, false);
	}
    }

    /// True if the name matches rhs
    template<class RHS_Type>
    const bool operator==(const option_base& lhs, const RHS_Type rhs);

    /// True if the names match
    const bool operator==(const option_base& lhs, const option_base& rhs);

    template<class RHS_Type>
    inline const bool operator==(const option_base& lhs, const RHS_Type rhs)
    {
	return lhs.name == rhs;
    }

    inline const bool operator==(const option_base& lhs, const option_base& rhs)
    {
	return lhs.name == rhs.name;
    }
}

#endif
