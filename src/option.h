#ifndef __OPTION_H__
#define __OPTION_H__

#include "arg_option.h"
#include "convert.h"


namespace libgetopt
{
    template<class Type>
    class option : public arg_option
    {
	public:

	    explicit option(const char short_opt);
	    explicit option(const std::string& long_opt);
	    option(const std::string& long_opt, const char opt);

	    operator const Type& () const;
	    const Type& get() const;

	    void set(const Type& arg);

	private:

	    Type m_arg;

	    bool parse_arg(char const * const optarg);
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
    inline bool option<Type>::parse_arg(char const * const optarg)
    {
	return convert<Type>(optarg, &m_arg, m_err_str);
    }

    template<class Type>
    inline const Type& option<Type>::get() const
    {
	return m_arg;
    }

    template<class Type>
    inline option<Type>::operator const Type& () const
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
