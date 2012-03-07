#ifndef __CMDLINE_LEXER_H__
#define __CMDLINE_LEXER_H__

namespace libgetopt
{
    class cmdline_token;

    /// Generates parameter tokens based on list of parameters
    /**
     *  Parameters are categorized into two types: named parameters
     *  and unnamed parameters.  Named parameters start with either a
     *  '-' or a "--".  If a parameter does not start with '-' or is
     *  just '-', or just "--" then it is an unnamed parameter.
     *
     *  Short named parameters are named paramters that start with a
     *  '-' followed by one character not including '-' representing
     *  the paramter's name.  The string after the '-' may be more
     *  than one character if an argument is given with the short
     *  named parameter, see below.
     *
     *  Short named parameters contain an argument only if the name
     *  and argument are one string.  For example, a parameter string
     *  of "-sabc" is considered to contain an argument.  The
     *  parameter name is "s" and the argument is "abc".  However, a
     *  parameter string of "-s abc" is not considered to contain an
     *  argument.  In this case, the parameter name is "-s" and there
     *  is no argument.
     *
     *  Long named parameters are named parameters that start with
     *  "--" followed by a string representing the parameter's name.
     *  The parameter's name is composed of all the characters up to
     *  but not including an optional '=' which is used to delimit a
     *  long named parameter from its argument, see below.
     *
     *  Long named parameters contain an argument only if the name and
     *  argument are one string delimited by an equals character.  For
     *  example, a parameter string of "--long=abc" is considered to
     *  contain an argument.  The parameter name is "long" and the
     *  argument is "abc".  However, a parameter string of "--long
     *  abc" is not considered to contain an argument.  In this case,
     *  the parameter name is "long" and there is no argument.
     *
     */
    class cmdline_lexer
    {
	public:

	    cmdline_lexer(int argc, char * const * argv);
	    cmdline_lexer();

	    /** Resets the cmdline_lexer
	     *
	     *  Causes the next call to next_parameter to start back
	     *  at the beginning of the arg list.
	     */
	    void reset();

	    /** Resets the cmdline_lexer
	     *
	     *  Causes the next call to next_parameter to use the new
	     *  arg list passed in.
	     */
	    void reset(int argc, char * const * argv);

	    /** Generates the token for the next parameter
	     *
	     *  @param token Pointer to a cmdline_token used to
	     *  describe the parameter parsed
	     *
	     *  @return true if token was filled, false otherwise
	     */
	    bool next_parameter(cmdline_token* token);

	private:

	    static void check_args(int argc, char * const * argv);

	    static void lex_named_parameter(cmdline_token& token);
	    static void lex_unnamed_parameter(cmdline_token& token);

	    //! The number of parameters to lex
	    int m_paramc;

	    //! The array of parameters to lex
	    char * const * m_paramv;

	    //! The index of the next m_paramv to lex
	    int m_paramv_idx;
    };

    inline cmdline_lexer::cmdline_lexer(int argc, char * const * argv):
	m_paramc(argc),
	m_paramv(argv),
	m_paramv_idx(0)
    {
	check_args(argc, argv);
    }

    inline cmdline_lexer::cmdline_lexer():
	m_paramc(0),
	m_paramv(NULL),
	m_paramv_idx(0)
    {}

    inline void cmdline_lexer::reset()
    {
	reset(m_paramc, m_paramv);
    }

    inline void cmdline_lexer::reset(int argc, char * const * argv)
    {
	check_args(argc, argv);
	m_paramc = argc;
	m_paramv = argv;
	m_paramv_idx = 0;
    }
}

#endif
