#include <algorithm>
#include <functional>
#include <string>
#include <cctype>

#include <iostream>

using namespace std;

#include "cmdline_parser.h"
#include "cmdline_token.h"
#include "cmdline_lexer.h"
#include "optional_arg_parser.h"
#include "option_base.h"
#include "ibasic_flag.h"
#include "ioption_base_visitor.h"

using namespace libgetopt;
using std::string;
using std::vector;

cmdline_parser::parser_token::parser_token(cmdline_token const * const token,
					   cmdline_lexer * const lexer,
					   cmdline_parser * const parser):
    m_token(token),
    m_lexer(lexer),
    m_parser(parser)
{}

cmdline_parser::parser_token::~parser_token() {}

cmdline_parser::parser_named_param::parser_named_param(named_parameter const * const param,
						       cmdline_token const * const token,
						       cmdline_lexer * const lexer,
						       cmdline_parser * const parser):
    parser_token(token, lexer, parser),
    m_param(param)
{}

cmdline_parser::parser_named_param::~parser_named_param() {}

cmdline_parser::parser_option::parser_option(option_base * const option,
					     cmdline_token const * const token,
					     cmdline_lexer * const lexer,
					     cmdline_parser* const parser):
    parser_named_param(option, token, lexer, parser),
    m_option(option)
{}

const parse_result cmdline_parser::parser_option::parse()
{
    return handle_arg_required(*m_option, *this);
}

void cmdline_parser::parser_option::visit(const string& arg) const
{
    cmdline_parser::parser_token::parser().invoke_option_visitors(*m_option, arg);
}

option_base * const cmdline_parser::find_option(option_base const * const opt) const
{
    option_list_t::const_iterator option =
	find_if(m_options.begin(), m_options.end(),
		bind2nd(ptr_fun(option_base::ptr_match), opt));

    if( option != m_options.end() )
    {
	return *option;
    }

    return NULL;
}

option_base * const cmdline_parser::find_option(const string& name) const
{
    option_list_t::const_iterator option =
	find_if(m_options.begin(), m_options.end(),
		bind2nd(ptr_fun(option_base::name_match), name));

    if( option != m_options.end() )
    {
	return *option;
    }

    return NULL;
}

auto_ptr<cmdline_parser::parser_token> cmdline_parser::find_token(cmdline_token const * token,
								  cmdline_lexer* lexer)
{
    option_base* temp = find_option(token->name());
    auto_ptr<parser_token> ptoken(NULL);

    if( temp != NULL )
    {
	ptoken = auto_ptr<parser_token>(new parser_option(temp, token, lexer, this));
    }

    return ptoken;
}

const bool cmdline_parser::find_token(const cmdline_token& token) const
{
    return ( find_option(token.name()) != NULL );
}

void cmdline_parser::add_option(option_base* opt)
{
    option_base const * option = find_option(opt);

    if( option != NULL )
    {
	throw duplicate_option(opt->name().string_name());
    }

    option = find_option(opt->name().string_name());

    if( option != NULL )
    {
	throw duplicate_option(opt->name().string_name());
    }

    m_options.push_back(opt);
}

void cmdline_parser::add_visitor(ioption_base_visitor* vis)
{

    option_visitor_list_t::const_iterator visitor = find(m_option_visitors.begin(),
							 m_option_visitors.end(),
							 vis);

    if( visitor == m_option_visitors.end() )
    {
	m_option_visitors.push_back(vis);
    }
    else
    {
	throw logic_error("duplicate visitor");
    }
}

void cmdline_parser::remove_visitor(ioption_base_visitor* vis)
{
    option_visitor_list_t::iterator visitor = find(m_option_visitors.begin(),
						   m_option_visitors.end(),
						   vis);

    if( visitor == m_option_visitors.end() )
    {
	throw logic_error("visitor not found");
    }

    m_option_visitors.erase(visitor);
}

void cmdline_parser::process_no_arg(ibasic_flag& flag, const parser_token& ptoken)
{
    flag.present(true);
    ptoken.visit("");
}

const parse_result cmdline_parser::process_arg(arg_parser& parser,
					       const string& arg,
					       const parser_named_param& ptoken)
{
    string error_str;

    // option failed to parse arg
    if( parser.parse_arg(arg.c_str(), &error_str) == false )
    {	
	return parse_result(ptoken.param().name(), arg, error_str);
    }

    ptoken.visit(arg);
    return parse_result();
}

void cmdline_parser::process_unnamed_param(const string& arg)
{

}

void cmdline_parser::invoke_option_visitors(option_base& option, const string& arg) const
{
    for(option_visitor_list_t::const_iterator i = m_option_visitors.begin();
	i != m_option_visitors.end();
	++i)
    {
	(*i)->visit(option, arg);
    }
}

const parse_result cmdline_parser::handle_no_arg(ibasic_flag& flag,
						 const parser_named_param& ptoken)
{
    if( ptoken.token().has_arg() == true )
    {
	// this option is not supposed to have an arg
	return parse_result(ptoken.param().name(),
			    ptoken.token().arg(),
			    "no argument required");
    }
    else
    {
	process_no_arg(flag, ptoken);
    }

    return parse_result();
}

const parse_result cmdline_parser::handle_arg_required(arg_parser& parser,
						       parser_named_param& ptoken)
{
    cmdline_token next_token;

    // argument given with the option
    if( ptoken.token().has_arg() )
    {
	return process_arg(parser, ptoken.token().arg(), ptoken);
    }

    // argument not given with the current token, so get another token
    if( ptoken.lexer().next_parameter(&next_token) == false )
    {
	// no argument given for the option and there are no more tokens
	return parse_result(ptoken.param().name());
    }

    // unnamed token use it as the argument
    if( next_token.is_unnamed() == true )
    {
	return process_arg(parser, next_token.parameter(), ptoken);
    }

    /* At this point the token is named so it requires more
     * examination */

    // The token is not a known option and is a number
    if( ( ptoken.parser().find_token(next_token) == false ) &&
	( token_isnum(next_token) == true ) )
    {
	return process_arg(parser, next_token.parameter(), ptoken);
    }

    // option missing argument
    return parse_result(ptoken.param().name());
}

const parse_result cmdline_parser::handle_arg_optional(optional_arg_parser& parser,
						       parser_named_param& ptoken)
{
    cmdline_token next_token;

    // pass the arg to the option
    if( ptoken.token().has_arg() == true )
    {
	return process_arg(parser, ptoken.token().arg(), ptoken);
    }

    // no arg given, get another token
    if( ptoken.lexer().next_parameter(&next_token) == false )
    {
	// no more tokens just process the flag
	process_no_arg(parser, ptoken);
	return parse_result();
    }

    if( next_token.is_unnamed() == true )
    {
	// next token is an unnamed parameter pass it to the option
	return process_arg(parser, next_token.parameter(), ptoken);
    }

    /* At this point the next token is named so we need to see if it's
     * a negative number or represents an option */
    
    auto_ptr<parser_token> next_ptoken = ptoken.parser().find_token(&next_token, &ptoken.lexer());

    /* if next_token is a named parameter, process the current named parameter and then
     * the next option */
    if( next_ptoken.get() != NULL )
    {
	process_no_arg(parser, ptoken);
	return next_ptoken->parse();
    }

    // next_token is a number pass it to the current option
    if( token_isnum(next_token) == true )
    {
	return process_arg(parser, next_token.parameter(), ptoken);
    }
    // next token is not a number
    else
    {
	process_no_arg(parser, ptoken);

	/* return invalid option since the named token
	 * does not represent a known option */
	return parse_result(next_token.name());
    }
}

const parse_result cmdline_parser::handle_token(const cmdline_token& token,
						cmdline_lexer& lexer)
{
    option_base* option = NULL;

    // token is an unnamed parameter
    if( token.is_unnamed() == true )
    {
	process_unnamed_param(token.parameter());
	return parse_result();
    }

    auto_ptr<parser_token> ptoken = find_token(&token, &lexer);

    // option found, handle it
    if( ptoken.get() != NULL )
    {
	return ptoken->parse();
    }

    // token is a negative number treat it like an unnamed parameter
    if( token_isnum(token) == true )
    {
	process_unnamed_param(token.parameter());
	return parse_result();
    }
    // token is a bad option
    else
    {
	return parse_result(token.name());
    }
}

const parse_result cmdline_parser::parse(int argc, char* const argv[])
{
    cmdline_lexer lexer(argc, argv);
    cmdline_token token;
    parse_result result;

    while( lexer.next_parameter(&token) == true )
    {
	result = handle_token(token, lexer);

	if( result.bad() == true )
	{
	    break;
	}
    };

    return result;
}

const bool libgetopt::token_isnum(const cmdline_token& token)
{
    /* A token is considered a number if it's a short name and the
     * first character in it's name is a number */
    if( ( token.type() == cmdline_token::short_named )
	&& ( isdigit(token.name()[0]) != 0 ) )
    {
	return true;
    }

    return false;
}
