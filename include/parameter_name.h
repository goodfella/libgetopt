#ifndef __PARAMETER_NAME_H__
#define __PARAMETER_NAME_H__

#include <string>
#include <stdexcept>
#include <cctype>

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
	    const std::string string_name() const;

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
	    char m_short_name;
    };

    /// True if the long name member to matches long_name
    bool operator==(const parameter_name& lhs, char const * const long_name);

    bool operator==(const parameter_name& lhs, const std::string& long_name);
    bool operator!=(const parameter_name& lhs, const std::string& long_name);

    /// true if either the short name or long name matches
    bool operator==(const parameter_name& lhs, const parameter_name& rhs);

    /// True if the short name member matches rhs
    bool operator==(const parameter_name& lhs, const int rhs);

    /// True if the short name member matches rhs
    bool operator==(const parameter_name& lhs, const char rhs);


    inline parameter_name::parameter_name(const std::string& long_name,
				    const char short_name):
	m_long_name(long_name),
	m_short_name(short_name)
    {
	check_name(long_name);
	check_name(short_name);
    }

    inline parameter_name::parameter_name(const std::string& long_name):
	m_long_name(long_name),
	m_short_name(0)
    {
	check_name(long_name);
    }

    inline parameter_name::parameter_name(const char short_name):
	m_long_name(""),
	m_short_name(short_name)
    {
	check_name(short_name);
    }

    inline const std::string& parameter_name::long_name() const
    {
	return m_long_name;
    }

    inline const char parameter_name::short_name() const
    {
	return m_short_name;
    }

    inline const bool parameter_name::has_long_name() const
    {
	return long_name() != "";
    }

    inline const bool parameter_name::has_short_name() const
    {
	return short_name() != 0;
    }

    inline bool operator==(const parameter_name& lhs, char const * const rhs)
    {
	return (lhs.long_name() == rhs || lhs.string_name() == rhs);
    }

    inline bool operator==(const parameter_name& lhs, const std::string& name)
    {
	return (lhs.long_name() == name || lhs.string_name() == name);
    }

    inline bool operator!=(const parameter_name& lhs, const std::string& name)
    {
	return (lhs.long_name() != name && lhs.string_name() != name);
    }

    inline bool operator==(const parameter_name& lhs, const parameter_name& rhs)
    {
	return ( lhs.short_name() == rhs.short_name() ||
		 lhs.long_name() == rhs.long_name() );
    }

    inline bool operator==(const parameter_name& lhs, const char rhs)
    {
	return rhs == lhs.short_name();
    }

    inline bool bad_name_char(const char ch)
    {
	return ! isgraph(ch);
    }
}

#endif
