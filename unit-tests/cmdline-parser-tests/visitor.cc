#include <iostream>
#include <string>
#include <stdexcept>

#include "libgetopt.h"
#include "libunit-test.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

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
    option<parse_arg_passed> opt1("opt1");
    option<parse_arg_passed> opt2("opt2", false);

    option_base_visitor visitor;

    cmdline_parser parser;

    parser.add_visitor(&visitor);

    try
    {
	parser.add_visitor(&visitor);
	cerr << "adding visitor twice did not throw an exception\n";
	return 1;
    }
    catch(logic_error& ex){}
    catch(...)
    {
	cerr << "adding visitor twice did not throw a logic_error exception\n";
	return 1;
    }


    parser.remove_visitor(&visitor);

    try
    {
	parser.remove_visitor(&visitor);
	cerr << "removing visitor twice did not throw an exception\n";
	return 1;
    }
    catch(logic_error& ex){}
    catch(...)
    {
	cerr << "adding visitor twice did not throw a logic_error exception\n";
	return 1;
    }

    parser.add_visitor(&visitor);

    parser.add_option(&opt1);
    parser.add_option(&opt2);

    cmdline_args args(argv[0]);

    args.add(&opt1, "abc");
    args.add(&opt2);

    parse_result res = parser.parse(args.count(), args);

    if( res.bad() == true )
    {
	cerr << "parsing failed and returned: " << res.result() << endl;
	return 1;
    }

    if( visitor.visited == false )
    {
	cerr << "option base visitor not visited\n";
	return 1;
    }

    if( visitor.count != 2 )
    {
	cerr << "visitor not visited enough\n";
	return 1;
    }

    return 0;
}
