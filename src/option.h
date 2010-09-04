#ifndef __OPTION_H__
#define __OPTION_H__

#include "arg_option_base.h"
#include "convert.h"


namespace libgetopt
{
    template<class Type>
    class option : public arg_option_base
    {
	public:

	    explicit option(char short_opt);
	    option(const std::string& long_opt, int val);
	    option(const std::string& long_opt, char opt);

	    operator const Type& () const;
	    const Type& get() const;

	    void set(const Type& arg);

	private:

	    Type m_arg;

	    bool parse_arg(char const * const optarg);
    };

    template<class Type>
    inline option<Type>::option(char short_opt):
	arg_option_base(short_opt)
    {}

    template<class Type>
    inline option<Type>::option(const std::string& long_opt, int val):
	arg_option_base(long_opt, val)
    {}

    template<class Type>
    inline option<Type>::option(const std::string& long_opt, char short_opt):
	arg_option_base(long_opt, short_opt)
    {}

    template<class Type>
    bool option<Type>::parse_arg(char const * const optarg)
    {
	return convert<Type>(optarg, &m_arg);
    }

    template<class Type>
    const Type& option<Type>::get() const
    {
	return m_arg;
    }

    template<class Type>
    option<Type>::operator const Type& () const
    {
	return m_arg;
    }

    template<class Type>
    void option<Type>::set(const Type& arg)
    {
	arg_option_base::set();
	m_arg = arg;
    }
}

#endif
