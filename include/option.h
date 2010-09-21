#ifndef __OPTION_H__
#define __OPTION_H__

#include "arg_option.h"


namespace libgetopt
{

    template<class Type>
    bool convert(char const * const optarg, Type* argp, std::string* error_str);

    template<class Type>
    class option : public arg_option
    {
	public:

	    explicit option(const char short_opt);
	    explicit option(const std::string& long_opt);
	    option(const std::string& long_opt, const char opt);

	    operator Type& ();
	    Type& get();

	    void set(const Type& arg);

	private:

	    Type m_arg;

	    bool parse(char const * const optarg, std::string* err_str);
    };

    template<class Type>
    inline option<Type>::option(const char short_opt):
	arg_option(short_opt)
    {}

    template<class Type>
    inline option<Type>::option(const std::string& long_opt):
	arg_option(long_opt)
    {}

    template<class Type>
    inline option<Type>::option(const std::string& long_opt, const char short_opt):
	arg_option(long_opt, short_opt)
    {}

    template<class Type>
    inline bool option<Type>::parse(char const * const optarg, std::string* err_str)
    {
	return convert<Type>(optarg, &m_arg, err_str);
    }

    template<class Type>
    inline Type& option<Type>::get()
    {
	return m_arg;
    }

    template<class Type>
    inline option<Type>::operator Type& ()
    {
	return m_arg;
    }

    template<class Type>
    void option<Type>::set(const Type& arg)
    {
	arg_option::present();
	m_valid_arg = true;
	m_arg = arg;
    }
}

#endif
