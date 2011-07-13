#ifndef __PARAMETER_NAME_H__
#define __PARAMETER_NAME_H__

#include <string>
#include <stdexcept>
#include <cctype>
#include <cstring>

namespace libgetopt
{
    /// Contains the option names for a given option
    class parameter_name
    {
	public:

	    parameter_name(const std::string& long_name, const char short_name);
	    explicit parameter_name(const std::string& long_name);
	    explicit parameter_name(const char short_name);

	    /// Returns the long name of an option
	    const std::string& long_name() const;

	    /// Returns the short name of an option
	    const char short_name() const;

	    /** Returns the string representation of the name
	     *
	     *  @return If there is a long name, then the long name is
	     *  returned.  If there is only a short name, then a
	     *  string representation of the short name is returned
	     */
	    const std::string& string_name() const;

	    /// Returns whether or not an option has a long name
	    const bool has_long_name() const;

	    /// Returns whether or not an option has a short name
	    const bool has_short_name() const;

	    class invalid_name: public std::logic_error
	    {
		public:

		    invalid_name(const std::string& err):
			std::logic_error(err)
		    {}
	    };

	    /** Checks if a string qualifies as a long name
	     *
	     *  Throws an invalid_name exception if long_name does not
	     *  qualify as a long option name
	     *
	     *  @param long_name String to check
	     */
	    static void check_name(const std::string& long_name);

	    /** Checks if a string qualifies as a short name
	     *
	     *  Throws an parameter_name::invalid_name exception if
	     *  short_name does not qualify as a short option name
	     *
	     *  @param short_name Character to check
	     */
	    static void check_name(const char short_name);

	private:

	    std::string m_long_name;
	    std::string m_short_name;
    };

    /// True if rhs to matches long_name() or string_name()
    bool operator==(const parameter_name& lhs, char const * const rhs);

    /// True if rhs does not match long_name() and string_name()
    bool operator!=(const parameter_name& lhs, char const * const rhs);


    /// See operator==(const parameter_name& lhs, char const * const rhs)
    bool operator==(const parameter_name& lhs, const std::string& rhs);

    /// See operator==(const parameter_name& lhs, char const * const rhs)
    bool operator!=(const parameter_name& lhs, const std::string& rhs);


    /** Checks if two parameter_name objects are equal
     *
     *  @return True both lhs and rhs have long names and the long
     *  names are equal.  Also true if both lhs and rhs have short
     *  names and the short names are equal.  False otherwise
     */
    bool operator==(const parameter_name& lhs, const parameter_name& rhs);

    /// Not of operator==(const parameter_name& lhs, const parameter_name& rhs)
    bool operator!=(const parameter_name& lhs, const parameter_name& rhs);


    /// True if the short name member matches rhs
    bool operator==(const parameter_name& lhs, const int rhs);

    /// Not of operator==(const parameter_name& lhs, const int rhs)
    bool operator!=(const parameter_name& lhs, const int rhs);


    /// True if the short name member matches rhs
    bool operator==(const parameter_name& lhs, const char rhs);

    /// Not of operator==(const parameter_name& lhs, const char rhs)
    bool operator!=(const parameter_name& lhs, const char rhs);


    inline parameter_name::parameter_name(const std::string& long_name,
				    const char short_name):
	m_long_name(long_name),
	m_short_name(1, short_name)
    {
	check_name(long_name);
	check_name(short_name);
    }

    inline parameter_name::parameter_name(const std::string& long_name):
	m_long_name(long_name),
	m_short_name("")
    {
	check_name(long_name);
    }

    inline parameter_name::parameter_name(const char short_name):
	m_long_name(""),
	m_short_name(1, short_name)
    {
	check_name(short_name);
    }

    inline const std::string& parameter_name::long_name() const
    {
	return m_long_name;
    }

    inline const char parameter_name::short_name() const
    {
	if( m_short_name != "" )
	{
	    return m_short_name[0];
	}
	else
	{
	    return '\0';
	}
    }

    inline const std::string& parameter_name::string_name() const
    {
	if( m_long_name != "" )
	{
	    return m_long_name;
	}
	else
	{
	    return m_short_name;
	}
    }

    inline const bool parameter_name::has_long_name() const
    {
	return long_name() != "";
    }

    inline const bool parameter_name::has_short_name() const
    {
	return short_name() != '\0';
    }

    inline bool operator==(const parameter_name& lhs, char const * const rhs)
    {
	if( strlen(rhs) == 0 )
	{
	    return false;
	}

	bool long_test = (lhs.long_name() == rhs);
	bool short_test = (lhs.short_name()== rhs[0]);
	return (long_test || short_test);
    }

    inline bool operator==(const parameter_name& lhs, const std::string& rhs)
    {
	return (lhs == rhs.c_str());
    }


    inline bool operator!=(const parameter_name& lhs, const parameter_name& rhs)
    {
	return ! (lhs == rhs);
    }

    inline bool operator!=(const parameter_name& lhs, char const * const rhs)
    {
	return ! (lhs == rhs);
    }

    inline bool operator!=(const parameter_name& lhs, const std::string& name)
    {
	return ! (lhs == name);
    }

    inline bool operator!=(const parameter_name& lhs, const char rhs)
    {
	return ! (lhs == rhs);
    }

    inline bool operator!=(const parameter_name& lhs, const int rhs)
    {
	return ! (lhs == rhs);
    }

    inline bool bad_name_char(const char ch)
    {
	return ! isgraph(ch);
    }
}

#endif
