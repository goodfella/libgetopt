#include <cstdio>
#include <string>

#include "option.h"
#include "cmdline_parser.h"

using namespace libgetopt;
using std::string;


int main(int argc, char** argv)
{
    option<double> double_opt("double", 'd');
    option<int> int_opt("int", 'i');
    option<string> string_opt("string", 's');

    cmdline_parser parser;

    parser.add_option(&double_opt);
    parser.add_option(&int_opt);
    parser.add_option(&string_opt);

    parser.parse(argc, argv);

    if( double_opt.is_set() == true )
    {
	printf("double option = %f\n", double_opt.get());
    }

    if( int_opt.is_set() == true )
    {
	printf("int option = %d\n", int_opt.get());
    }

    if( string_opt.is_set() == true )
    {
	printf("string option = %s\n", string_opt.get().c_str());
    }
}
