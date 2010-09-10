#include <limits>
#include <cstdio>
#include <string>

#include "option.h"
#include "cmdline_parser.h"

using namespace libgetopt;
using namespace std;


int main(int argc, char** argv)
{
    printf("int max: %d, int min: %d\n",
	   numeric_limits<int>::max(),
	   numeric_limits<int>::min());

    option<double> double_opt("double", 'd');
    option<int> int_opt("int", 'i');
    option<string> string_opt("string", 's');
    option<long> long_opt("long", 'l');

    cmdline_parser parser;

    parser.add_option(&double_opt);
    parser.add_option(&int_opt);
    parser.add_option(&string_opt);
    parser.add_option(&long_opt);

    cmdline_parser::parse_result res;

    res = parser.parse(argc, argv);

    if( res.bad() )
    {
	printf("command line parsing failed\n");

	if( res == cmdline_parser::parse_result::result_missing_arg )
	{
	    printf("option: %s, missing arg\n", res.option_name.c_str());
	}
	else if( res == cmdline_parser::parse_result::result_invalid_arg )
	{
	    printf("option: %s, invalid arg: %s\n",
		   res.option_name.c_str(),
		   res.error_string.c_str());
	}

	return 1;
    }

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

    if( long_opt.is_set() == true )
    {
	printf("long option = %ld\n", long_opt.get());
    }

    return 0;
}
