#ifndef __CMDLINE_PARSER_H__
#define __CMDLINE_PARSER_H__

#include <vector>
#include <stdexcept>
#include <string>
#include <functional>
#include <memory>

#include "parse_result.h"

namespace libgetopt
{
    class named_parameter;
    class option_base;
    class arg_parser;
    class ioption_base_visitor;
    class cmdline_token;
    class cmdline_lexer;

    class duplicate_option : public std::logic_error
    {
	public:

	explicit duplicate_option(const std::string& option_name):
	    logic_error("duplicate option: " + option_name)
	    {}
    };

    /** Parses the command line
     *
     *  Options are added to this class with the add_option() method.
     *  After adding the options the command line can be parsed with
     *  the parse() method.
     *
     */
    class cmdline_parser
    {
	public:

	    cmdline_parser() {}

	    /**  Adds an option to the list of accepted options
	     *
	     *   @param opt The option to add
	     *
	     *   @note throws a duplicate_option exception if a
	     *   previously added option with the same parameter_name
	     *   exists.
	     */
	    void add_option(option_base * opt);

	    /** Parses the command line
	     *
	     *  @param argc The number of parameters that exist in
	     *  argv
	     *
	     *  @param argv The command line parameters to parse
	     *
	     */
	const parse_result parse(int argc, char* const argv[]);

	    /** Adds a visitor to the visitor list
	     *
	     *  @note If the visitor has allready been added, a
	     *  std::logic_error exception is thrown.
	     *
	     *  @param visitor visitor to add to the list
	     */
	    void add_visitor(ioption_base_visitor* visitor);

	    /** Removes a visitor from the visitor list
	     *
	     *  @note If the visitor has not allready been added, a
	     *  std::logic_error exception is thrown.
	     *
	     *  @param visitor visitor to remove from the list
	     */
	    void remove_visitor(ioption_base_visitor* visitor);

	private:

	    typedef std::vector<ioption_base_visitor*> option_visitor_list_t;
	    typedef std::vector<option_base*> option_list_t;

	class parser_token
	{
	    public:
	    
	    parser_token(cmdline_token const * token, cmdline_lexer* lexer,
			 cmdline_parser* parser);

	    virtual ~parser_token();
	    virtual const parse_result parse() = 0;
	    virtual void visit(const std::string& arg) const = 0;

	    cmdline_lexer& lexer();
	    cmdline_parser& parser();
	    const cmdline_parser& parser() const;
	    const cmdline_token& token() const;

	    private:

	    cmdline_token const * m_token;
	    cmdline_lexer* m_lexer;
	    cmdline_parser* m_parser;
	};
	
	class option_token: public parser_token
	{
	    public:

	    option_token(option_base* option, cmdline_token const * token,
			 cmdline_lexer* lexer,
			 cmdline_parser* parser);
	    
	    const parse_result parse();
	    void visit(const std::string& arg) const;
	    
	    private:
	    
	    option_base* m_option;
	};

	    // no copying allowed
	    cmdline_parser(const cmdline_parser&);
	    cmdline_parser& operator = (const cmdline_parser&);

	option_base * const find_option(option_base const * const opt) const;

	option_base * const find_option(const std::string& name) const;

	std::auto_ptr<parser_token> find_token(cmdline_token const *token,
					       cmdline_lexer* lexer);

	const bool find_token(const cmdline_token& token) const;

	void invoke_option_visitors(option_base& option, const std::string& arg) const;

	static const parse_result process_arg(arg_parser& parser, const std::string& arg,
					      const parser_token& ptoken);

	static void process_unnamed_param(const std::string& arg);

	static void process_named_param(named_parameter& option,
					const parser_token& ptoken);

	const parse_result handle_token(const cmdline_token& token, cmdline_lexer& lexer);

	static const parse_result handle_arg_parser(arg_parser& parser,
						    parser_token& ptoken);

	static const parse_result handle_arg_required(arg_parser& option,
						      parser_token& ptoken);

	static const parse_result handle_arg_optional(arg_parser& option,
						      parser_token& ptoken);
	
	static const parse_result handle_no_arg(named_parameter& option,
						parser_token& ptoken);

	option_list_t m_options;
	option_visitor_list_t m_option_visitors;
    };

    inline cmdline_lexer& cmdline_parser::parser_token::lexer()
    {
	return *m_lexer;
    }
    
    inline cmdline_parser& cmdline_parser::parser_token::parser()
    {
	return *m_parser;
    }

    inline const cmdline_parser& cmdline_parser::parser_token::parser() const
    {
	return *m_parser;
    }

    inline const cmdline_token& cmdline_parser::parser_token::token() const
    {
	return *m_token;
    }

    const bool token_isnum(const cmdline_token& token);
}

#endif
