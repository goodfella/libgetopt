#include <iostream>
#include <string>

#include "libgetopt.h"
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

struct option_visitor: ioption_visitor<string>
{
	option_visitor(): visited(true), count(0) {}

	void visit(option<string>& opt, const string& arg)
	{
	    visited = true;
	    ++count;
	}

	bool visited;
	int count;
};

struct option_base_visitor: ioption_base_visitor
{
	option_base_visitor(): visited(false), count(0) {}

	void visit(option_base& opt, const string& arg)
	{
	    visited = true;
	    ++count;
	}

	bool visited;
	int count;
};

int main(int argc, char** argv)
{
    option<string> opt1("opt1");
    option<string> opt2("opt2");

    option_visitor opt1_visitor;
    option_base_visitor opt1_base_visitor;

    opt1.visitor(&opt1_visitor);
    opt1.base_visitor(&opt1_base_visitor);

    opt2.visitor(&opt1_visitor);
    opt2.base_visitor(&opt1_base_visitor);

    cmdline_parser parser;

    parser.add_option(&opt1);
    parser.add_option(&opt2);

    cmdline_args args(argv[0]);

    args.add(&opt1, "abc");
    args.add(&opt2, "abc2");

    parse_result res = parser.parse(args.count(), args);

    if( res.bad() == true )
    {
	cerr << "parsing failed and returned: " << res.result() << endl;
	return 1;
    }

    if( opt1.present() == false )
    {
	cerr << "option is not present\n";
	return 1;
    }

    if( opt1_base_visitor.visited == false )
    {
	cerr << "option base visitor not visited\n";
	return 1;
    }

    if( opt1_base_visitor.count != 2 )
    {
	cerr << "option base_visitor not visited enough\n";
	return 1;
    }

    if( opt1_visitor.visited == false )
    {
	cerr << "option visitor not visited\n";
	return 1;
    }

    if( opt1_visitor.count != 2 )
    {
	cerr << "option visitor not visited enough\n";
	return 1;
    }

    return 0;
}
