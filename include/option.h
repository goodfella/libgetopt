#ifndef __OPTION_H__
#define __OPTION_H__

#include "option_base.h"
#include "string_cast.h"


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

	    /** Constructs an option class with a short name
	     *
	     *  @param short_name The char to use as the short name
	     *
	     *  @param arg_required True if an argument is required,
	     *  this is the default.  False if an argument is optional
	     */
	    option(const char short_name, bool arg_required = true);

	    /** Constructs an option class with a long name
	     *
	     *  @param long_name The string to use as the long name
	     *
	     *  @param arg_required True if an argument is required,
	     *  this is the default.  False if an argument is optional
	     */
	    option(const std::string& long_name, bool arg_required = true);

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
	    Type& get_arg();

	    /// Sets the argument
	    void set_arg(const Type& arg);

	private:

	    const bool __parse_arg(char const * const optarg, std::string* const err_str);
    };

    template<class Type>
    inline option<Type>::option(const char short_opt, bool arg_required):
	option_base(short_opt, arg_required)
    {
	option_base::m_arg = new Type();
    }

    template<class Type>
    inline option<Type>::option(const std::string& long_opt, bool arg_required):
	option_base(long_opt, arg_required)
    {
	option_base::m_arg = new Type();
    }

    template<class Type>
    inline option<Type>::option(const std::string& long_opt,
				const char short_opt,
				bool arg_required):
	option_base(long_opt, short_opt, arg_required)
    {
	option_base::m_arg = new Type();
    }

    template<class Type>
    option<Type>::~option()
    {
	delete static_cast<Type*>(option_base::m_arg);
    }

    template<class Type>
    const bool option<Type>::__parse_arg(char const * const optarg,
					 std::string* const err_str)
    {
	option_base::set_present_no_throw(true);
	return string_cast<Type>(optarg, static_cast<Type*>(option_base::m_arg),
				 err_str);
    }

    template<class Type>
    inline Type& option<Type>::get_arg()
    {
	return *(static_cast<Type*>(option_base::m_arg));
    }

    template<class Type>
    void option<Type>::set_arg(const Type& arg)
    {
	option_base::set_present_no_throw(true);
	*static_cast<Type*>(option_base::m_arg) = arg;
	arg_parser::set_arg_present_valid(true);
    }
}

#endif
