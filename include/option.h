#ifndef __OPTION_H__
#define __OPTION_H__

#include "option_base.h"
#include "string_cast.h"
#include "ioption_visitor.h"


namespace libgetopt
{
    /** Represents a command line option
     *
     *  The option class is responsible for parsing arguments from the
     *  command line.  It is declared to take a given type and given a
     *  long name, a short name or both.  The option class can be
     *  configured so that an argument is either required or optional
     */
    template<class Type>
    class option : public option_base
    {
	public:

	    typedef Type arg_type_t;

	    /** Constructs an option class with a short name
	     *
	     *  @param short_name The char to use as the short name
	     *
	     *  @param arg_required True if an argument is required,
	     *  this is the default.  False if an argument is optional
	     */
	    explicit option(const char short_name, bool arg_required = true);

	    /** Constructs an option class with a long name
	     *
	     *  @param long_name The string to use as the long name
	     *
	     *  @param arg_required True if an argument is required,
	     *  this is the default.  False if an argument is optional
	     */
	    explicit option(const std::string& long_name, bool arg_required = true);

	    /** Constructs an option class with a long name and short name
	     *
	     *  @param long_name The string to use as the long name
	     *  @param short_name The char to use as the short name
	     *
	     *  @param arg_required True if an argument is required,
	     *  this is the default.  False if an argument is optional
	     */
	    option(const std::string& long_name, const char short_name, bool arg_required = true);

	    ~option();

	    /// Returns the argument that has been parsed
	    Type& arg();

	    const Type& arg() const;

	    /// Sets the argument
	    void arg(const Type& arg);

	    /** Sets the visitor
	     *
	     *  Passing a NULL pointer clears the visitor
	     */
	    void visitor(ioption_visitor<Type>* vis);

	private:

	    const bool option_parse_arg(char const * const optarg, std::string* const err_str);

	    void derived_visit(const std::string& arg);
    };

    template<class Type>
    inline option<Type>::option(const char short_name, bool arg_required):
	option_base(short_name, arg_required)
    {
	option_base::m_arg = new Type();
    }

    template<class Type>
    inline option<Type>::option(const std::string& long_name, bool arg_required):
	option_base(long_name, arg_required)
    {
	option_base::m_arg = new Type();
    }

    template<class Type>
    inline option<Type>::option(const std::string& long_name,
				const char short_name,
				bool arg_required):
	option_base(long_name, short_name, arg_required)
    {
	option_base::m_arg = new Type();
    }

    template<class Type>
    inline option<Type>::~option()
    {
	delete &arg();
    }

    template<class Type>
    inline const bool option<Type>::option_parse_arg(char const * const optarg,
						     std::string* const err_str)
    {
	return string_cast<Type>::cast(optarg, &arg(), err_str);
    }

    template<class Type>
    inline Type& option<Type>::arg()
    {
	return *(static_cast<Type*>(option_base::m_arg));
    }

    template<class Type>
    inline const Type& option<Type>::arg() const
    {
	return *(static_cast<Type*>(option_base::m_arg));
    }

    template<class Type>
    void option<Type>::arg(const Type& new_arg)
    {
	Type& my_arg = arg();
	my_arg = new_arg;
	option_base::set_present_no_throw(true);
	arg_parser::set_arg_present_valid();
    }

    template<class Type>
    void option<Type>::derived_visit(const std::string& arg)
    {
	if( option_base::m_visitor != NULL )
	{
	    (static_cast<ioption_visitor<Type>*>(option_base::m_visitor))->visit(*this, arg);
	}
    }

    template<class Type>
    void option<Type>::visitor(ioption_visitor<Type>* vis)
    {
	option_base::m_visitor = vis;
    }
}

#endif
