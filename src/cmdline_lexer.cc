#include <stdexcept>
#include <cassert>
#include <cstring>
#include <algorithm>

#include "cmdline_lexer.h"
#include "cmdline_token.h"

using namespace std;
using namespace libgetopt;

void cmdline_lexer::check_args(int argc, char * const * argv)
{
    if( argc > 0 && argv == NULL )
    {
	throw logic_error(string("argc > 0 and argv is NULL, cmdline_lexer::") + __FUNCTION__);
    }

    if( argc < 0 )
    {
	throw logic_error(string("argc < 0, cmdline_lexer::") + __FUNCTION__);
    }
}

bool cmdline_lexer::next_parameter(cmdline_token* token)
{
    if( token == NULL )
    {
	throw logic_error("token is NULL");
    }

    token->parameter("");
    token->name("");
    token->arg("");
    token->type(cmdline_token::unknown);

    // no parameters to parse
    if( m_paramc == 0 || m_paramv == NULL )
    {
	return false;
    }

    if( m_paramv_idx >= m_paramc )
    {
	return false;
    }

    token->parameter().assign(m_paramv[m_paramv_idx]);

    // "--" is considered an unnamed parameter
    if( token->parameter() == "--" )
    {
	lex_unnamed_parameter(*token);
    }
    // named parameter
    else if( token->parameter()[0] == '-' && token->parameter().length() > 1 )
    {
	lex_named_parameter(*token);
    }
    // does not start with '-' or is just '-'
    else
    {
	lex_unnamed_parameter(*token);
    }

    ++m_paramv_idx;

    return true;
}

void cmdline_lexer::lex_unnamed_parameter(cmdline_token& token)
{
    token.name("");
    token.type(cmdline_token::unnamed);
    token.arg("");
}

void cmdline_lexer::lex_named_parameter(cmdline_token& token)
{
    // long name
    if( token.parameter()[1] == '-' )
    {
	// skip the --, and the first leter of the name since it could be a '='
	string::iterator start_of_equals = find(token.parameter().begin() + 3,
						token.parameter().end(),
						'=');

	token.name().assign(token.parameter().begin() + 2, start_of_equals);
	token.type() = cmdline_token::long_named;

	if( start_of_equals != token.parameter().end() )
	{
	    // skip the equals sign
	    token.arg().assign(start_of_equals + 1, token.parameter().end());
	}
	else
	{
	    token.arg("");
	}
    }

    // short name
    else
    {
	// make sure to not include an argument here
	token.name().assign(1, token.parameter()[1]);
	token.arg().assign(token.parameter().begin() + 2, token.parameter().end());
	token.type() = cmdline_token::short_named;
    }
}
