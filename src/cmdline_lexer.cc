#include <stdexcept>
#include <cassert>
#include <cstring>

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
}

bool cmdline_lexer::next_parameter(cmdline_token* token)
{
    if( token == NULL )
    {
	throw logic_error("token is NULL");
    }

    token->parameter = "";
    token->name = "";
    token->arg = "";

    if( m_paramv == NULL )
    {
	return false;
    }

    if( m_paramc == 0 )
    {
	return false;
    }

    if( m_param_idx >= m_paramc )
    {
	return false;
    }

    char* param = m_paramv[m_param_idx];

    token->parameter = param;
    size_t param_length = strlen(param);

    // "--" is considered an unnamed parameter
    if( strcmp(param, "--") == 0 )
    {
	lex_unnamed_parameter(param, *token);
    }
    // named parameter
    else if( param[0] == '-' && param_length > 1 )
    {
	lex_named_parameter(param, *token);
    }
    // does not start with '-' or is just '-'
    else
    {
	lex_unnamed_parameter(param, *token);
    }

    ++m_param_idx;

    return true;
}

void cmdline_lexer::lex_unnamed_parameter(char const * const parameter,
					  cmdline_token& token)
{
    assert(parameter != NULL);
    token.name = "";
    token.type = cmdline_token::unnamed;
    token.arg = "";
}

void cmdline_lexer::lex_named_parameter(char const * const parameter,
					cmdline_token& token)
{
    assert(parameter != NULL);

    // long name
    if( parameter[1] == '-' )
    {
	char const * const name = &parameter[2];

	// make sure not to include an argument passed with '=' in the name
	size_t name_length = strcspn(name + 1, "=") + 1;
	token.name.assign(name, name_length);
	token.type = cmdline_token::long_named;

	// arg passed with an equal sign
	if( name[name_length] == '=' )
	{
	    size_t arg_length = strlen(&name[name_length + 1]);
	    if( arg_length > 0 )
	    {
		token.arg.assign(&name[name_length + 1], arg_length);
	    }
	    // no arg after equals sign
	    else
	    {
		token.arg = "";
	    }
	}

	// no equals sign
	else
	{
	    token.arg = "";
	}
    }

    // short name
    else
    {
	// make sure to not include an argument here
	token.name.assign(1, parameter[1]);
	token.type = cmdline_token::short_named;

	size_t short_arg_len = strlen(&parameter[2]);

	if( short_arg_len > 0 )
	{
	    token.arg.assign(&parameter[2]);
	}
	else
	{
	    token.arg = "";
	}
    }
}
