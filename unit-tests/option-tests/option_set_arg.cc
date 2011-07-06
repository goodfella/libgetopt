#include <string>
#include <iostream>
#include "libgetopt.h"

using namespace libgetopt;
using namespace std;

int main(int argc, char** argv)
{
    option<string> opt("opt");

    string new_arg = "new_arg";

    opt.set_arg(new_arg);

    if( opt.get_arg() != new_arg )
    {
	cerr << "arg not set\n";
	return 1;
    }

    if( opt.is_present() == false )
    {
	cerr << "arg set but option::is_present is false\n";
	return 1;
    }

    if( opt.arg_present() == false )
    {
	cerr << "arg set but arg_parser::arg_present is false\n";
	return 1;
    }

    if( opt.arg_valid() == false )
    {
	cerr << "arg set but arg_parser::arg_valid is false\n";
	return 1;
    }

    opt.set_present(false);

    if( opt.is_present() == true )
    {
	cerr << "cleared present flag but is_present is still true\n";
	return 1;
    }

    if( opt.arg_present() == true )
    {
	cerr << "cleared present flag but arg_present is still true\n";
	return 1;
    }

    if( opt.arg_valid() == true )
    {
	cerr << "cleared present flag but arg_valid is still true\n";
	return 1;
    }

    return 0;
}
