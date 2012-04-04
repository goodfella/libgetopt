#ifndef __OPTION_BASE_H__
#define __OPTION_BASE_H__

#include <string>

#include "parameter_name.h"
#include "arg_parser.h"

namespace libgetopt
{
    class ioption_base_visitor;

    /// Base class for the option classes
    class option_base: public arg_parser
    {
	public:

	option_base(const std::string& long_name,
		    const char short_name,
		    const bool arg_required);

	explicit option_base(const std::string& long_name,
			     const bool arg_required);

	explicit option_base(const char short_name,
			     const bool arg_required);

	    virtual ~option_base();

	    /** Sets whether or not an option is present
	     *
	     *  @param is_present Present or not present
	     */
	    void present(const bool is_present);

	    /// Returns whether or not the option is present
	    const bool present() const;

	const bool derived_parse_arg(char const * const optarg,
				     std::string* const err_str);

	    void base_visitor(ioption_base_visitor* visitor);

	    /** True if two option_base classes passed as pointers match
	     *
	     *  This function is to be used as a predicate in standard
	     *  algorithms for lists of option_base pointers.
	     */
	    static const bool ptr_match(option_base const * const lhs,
					option_base const * const rhs);

	/** True if rhs matches the name of lhs
	 *
	 *  This function is to be used as a predicate in standard
	 *  algorithms.
	 */
	static const bool name_match(option_base const * const lhs,
				     const std::string& rhs);

	protected:

	    void set_present_no_throw(bool is_present);

	    /// Dispatches the visitor attached to the option
	    void visit(const std::string& arg);

	    void* m_arg;
	    void* m_visitor;

	private:

	    // No copying
	    option_base(const option_base&);
	    option_base& operator=(const option_base&);

	virtual void derived_visit(const std::string& arg) = 0;

	virtual const bool option_parse_arg(char const * const optarg,
					    std::string* const err_str) = 0;

	    ioption_base_visitor* m_base_visitor;
	    bool m_present;
    };

    inline arg_parser::arg_policy_t option_arg_policy(const bool arg_required)
    {
	return arg_required == true ? arg_parser::arg_required : arg_parser::arg_optional;
    }

    inline option_base::option_base(const std::string& long_name,
				    const char short_name,
				    const bool arg_required):
	arg_parser(long_name, short_name, option_arg_policy(arg_required)),
	m_arg(NULL),
	m_visitor(NULL),
	m_base_visitor(NULL),
	m_present(false)
    {}

    inline option_base::option_base(const std::string& long_name,
				    const bool arg_required):
	arg_parser(long_name, option_arg_policy(arg_required)),
	m_arg(NULL),
	m_visitor(NULL),
	m_base_visitor(NULL),
	m_present(false)
    {}

    inline option_base::option_base(const char short_name,
				    const bool arg_required):
	arg_parser(short_name, option_arg_policy(arg_required)),
	m_arg(NULL),
	m_visitor(NULL),
	m_base_visitor(NULL),
	m_present(false)
    {}

    inline const bool option_base::present() const
    {
	return m_present;
    }

    inline void option_base::set_present_no_throw(bool is_present)
    {
	m_present = is_present;

	if( is_present == false )
	{
	    arg_parser::clear_arg_present();
	}
    }

    inline void option_base::base_visitor(ioption_base_visitor* visitor)
    {
	m_base_visitor = visitor;
    }

    /// True if the name matches rhs
    template<class RHS_Type>
    const bool operator==(const option_base& lhs, const RHS_Type rhs);

    /// True if the names match
    const bool operator==(const option_base& lhs, const option_base& rhs);

    template<class RHS_Type>
    inline const bool operator==(const option_base& lhs, const RHS_Type rhs)
    {
	return lhs.name() == rhs;
    }

    inline const bool operator==(const option_base& lhs, const option_base& rhs)
    {
	return lhs.name() == rhs.name();
    }
}

#endif
