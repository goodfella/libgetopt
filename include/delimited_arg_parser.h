#ifndef __DELIMITED_ARG_PARSER_H__
#define __DELIMITED_ARG_PARSER_H__

#include <vector>
#include <cstddef>
#include <string>
#include <memory>

#include "string_cast.h"
#include "libgetopt_string.h"

namespace libgetopt
{
    /// Parses a string containing delimited Arg_Type values
    template<class Arg_Type>
    class delimited_arg_parser
    {
	public:

	    typedef Arg_Type& reference_t;
	    typedef const reference_t const_reference_t;

	    typedef std::vector<Arg_Type> container_t;

	    typedef typename container_t::iterator iterator_t;
	    typedef const iterator_t const_iterator_t;
	    typedef typename container_t::reverse_iterator reverse_iterator_t;
	    typedef const reverse_iterator_t const_reverse_iterator_t;

	    /// Constructs the class with the delimiter set to comma
	    delimited_arg_parser();

	    /// Constructs the class setting delimiter
	    explicit delimited_arg_parser(char delimiter);

	    /** Sets the delimiter
	     *
	     *  @param delimiter char to set the delimiter to
	     *
	     *  @note delimiter must be a graphical character
	     */
	    void delimiter(char delimiter);

	    /// Get the delimiter
	    const std::string& delimiter() const;

	    /// Returns the argument container
	    container_t& args();

	    /// Returns the argument container
	    const container_t& args() const;

	    bool operator()(char const * const arg, std::string* err_str);

	private:

	    std::string m_delimiter;
	    std::vector<Arg_Type> m_args;
    };

    template<class T>
    inline delimited_arg_parser<T>::delimited_arg_parser(): m_delimiter(1, ',') {}

    template<class T>
    inline delimited_arg_parser<T>::delimited_arg_parser(char delimiter):
	m_delimiter(1, delimiter)
    {}

    template<class T>
    inline void delimited_arg_parser<T>::delimiter(char delimiter)
    {
	m_delimiter = delimiter;
    }

    template<class T>
    inline const std::string& delimited_arg_parser<T>::delimiter() const
    {
	return m_delimiter;
    }

    template<class T>
    inline typename delimited_arg_parser<T>::container_t&
    delimited_arg_parser<T>::args()
    {
	return m_args;
    }

    template<class T>
    inline const typename delimited_arg_parser<T>::container_t&
    delimited_arg_parser<T>::args() const
    {
	return m_args;
    }

    template<class T>
    inline bool delimited_arg_parser<T>::operator() (char const * const optarg,
						     std::string* err_str)
    {
	const auto_cstring_ptr cstr(duplicate_cstring(optarg));

	T arg;

	char* tok = strtok(cstr.get(), m_delimiter.c_str());
	while(tok != NULL)
	{
	    if( string_cast<T>::cast(tok, &arg, err_str) == true )
	    {
		m_args.push_back(arg);
	    }
	    else
	    {
		return false;
	    }

	    tok = strtok(NULL, m_delimiter.c_str());
	}

	return true;
    }
}

#endif
