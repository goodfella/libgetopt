#ifndef __CMDLINE_PARSER_H__
#define __CMDLINE_PARSER_H__

#include <vector>
#include <stdexcept>
#include <string>

#include "option_base.h"
#include "parse_result.h"

namespace libgetopt
{
    class ioption_base_visitor;

    struct option_map
    {
	    explicit option_map(option_base* opt): val(0), option(opt) {}

	    bool operator==(int rhs) const
	    { return val == rhs; }

	    bool operator==(option_base const * const opt) const
	    { return option_base::ptr_match(option, opt); }

	    int val;
	    option_base *option;
    };

    class duplicate_option : public std::logic_error
    {
	public:

	    explicit duplicate_option(const std::string& option_name):
		logic_error("duplicate option: " + option_name)
	    {}
    };

    class parser_in_use: public std::logic_error
    {
	public:

	    parser_in_use(): logic_error("parser already in use") {}
    };

    typedef std::vector<option_map> option_list_t;

    /** Parses the command line using getopt
     *
     *  options are added to this class with the add_option() method.
     *  After adding the options the command line can be parsed with
     *  the parse() method.
     *
     *  @note The parse() method can only be called once globaly due
     *  to limitations of getopt.
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
	     *  @note This function can only be called once.
	     */
	    parse_result parse(int argc, char* const argv[]);

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

	    typedef std::vector<ioption_base_visitor*> visitor_list_t;

	    // no copying allowed
	    cmdline_parser(const cmdline_parser&);
	    cmdline_parser& operator = (const cmdline_parser&);

	    static option_base const * const find_option(option_base const * const opt,
							 const option_list_t& options);

	    option_list_t m_options;
	    static bool is_in_use;
	    visitor_list_t m_visitors;
    };
}

#endif
