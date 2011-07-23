#ifndef __CUSTOM_PARSER_H__
#define __CUSTOM_PARSER_H__

#include "custom_parser_base.h"

namespace libgetopt
{
    /** Encaptulates a parser class
     *
     *  This class allows for customized argument parsers.  The
     *  template parameter must be copyable and have an empty
     *  constructor.  The template parameter also must implement the
     *  function call operator with the following signature:
     *
     *  bool operator()(char const * const, std::string*)
     */
    template<class Parser_Type>
    class custom_parser: private custom_parser_base
    {
	public:

	    typedef Parser_Type parser_t;

	    custom_parser();
	    custom_parser(const custom_parser<Parser_Type>& parser);
	    custom_parser<Parser_Type>& operator= (const custom_parser<Parser_Type>& parser);

	    ~custom_parser();


	    /** Sets the parser
	     *
	     *  @param parser The parser to use.
	     */
	    void parser(const Parser_Type& parser);

	    /// Returns the parser
	    Parser_Type& parser();
	    const Parser_Type& parser() const;
    };

    template<class T>
    inline custom_parser<T>::custom_parser()
    {
	custom_parser_base::m_parser = new T();
    }

    template<class T>
    inline custom_parser<T>::custom_parser(const custom_parser<T>& parser)
    {
	custom_parser_base::m_parser = new T(parser.parser());
    }

    template<class T>
    custom_parser<T>& custom_parser<T>::operator= (const custom_parser<T>& parser)
    {
	custom_parser<T> temp(parser);
	std::swap<custom_parser_base>(*this, temp);
	return *this;
    }

    template<class T>
    inline custom_parser<T>::~custom_parser()
    {
	delete static_cast<T*>(custom_parser::m_parser);
    }

    template<class T>
    inline void custom_parser<T>::parser(const T& parser)
    {
	*(static_cast<T*>(custom_parser_base::m_parser)) = parser;
    }

    template<class T>
    inline T& custom_parser<T>::parser()
    {
	return *static_cast<T*>(custom_parser_base::m_parser);
    }

    template<class T>
    inline const T& custom_parser<T>::parser() const
    {
	return *static_cast<T*>(custom_parser_base::m_parser);
    }
}

#endif
