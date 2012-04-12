#ifndef __NAMED_PARAM_H__
#define __NAMED_PARAM_H__

#include <string>
#include "parameter_name.h"

namespace libgetopt
{
    class named_parameter
    {
	public:

	named_parameter(const std::string& long_name, const char short_name);
	explicit named_parameter(const std::string& long_name);
	explicit named_parameter(const char short_name);
	explicit named_parameter(const parameter_name& name);

	virtual ~named_parameter() = 0;

	/** Returns whether or not the named parameter is present
	 *
	 *  @return true if the parameter is present, false otherwise
	 */
	virtual const bool present() const = 0;

	/// Returns the parameters name
	const parameter_name& name() const;

	private:

	parameter_name m_name;
    };

    inline named_parameter::named_parameter(const std::string& long_name, const char short_name):
	m_name(long_name, short_name)
    {}

    inline named_parameter::named_parameter(const std::string& long_name):
	m_name(long_name)
    {}

    inline named_parameter::named_parameter(const char short_name):
	m_name(short_name)
    {}

    inline named_parameter::named_parameter(const parameter_name& name):
	m_name(name)
    {}

    inline const parameter_name& named_parameter::name() const
    {
	return m_name;
    }
}

#endif
