#ifndef __CUSTOM_PARSER_BASE_H__
#define __CUSTOM_PARSER_BASE_H__

namespace libgetopt
{
    struct custom_parser_base
    {
	    void* m_parser;
    };
}

template<class T>
void std::swap(libgetopt::custom_parser_base& a,
	       libgetopt::custom_parser_base& b)
{
    void* temp = a.m_parser;
    a.m_parser = b.m_parser;
    b.m_parser = temp;
}

#endif
