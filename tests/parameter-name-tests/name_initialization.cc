#include <iostream>
#include <stdexcept>

#include "libgetopt.h"

using namespace std;
using namespace libgetopt;

struct initialization_error: public logic_error
{
	initialization_error(const string& msg):
	    logic_error(msg)
	{}
};

const char short_name = 's';
const string short_name_str = "s";
const string long_name = "long-name";

void test_short_name(const parameter_name& name)
{
    if( name.has_short_name() == false )
    {
	throw initialization_error("name.has_short_name() is incorrect");
    }

    if( name.short_name() != short_name )
    {
	throw initialization_error("name.short_name() is incorrect");
    }
}

void test_long_name(const parameter_name& name)
{
    if( name.has_long_name() == false )
    {
	throw initialization_error("name.has_long_name() is incorrect");
    }

    if( name.long_name() != long_name )
    {
	throw initialization_error("name.long_name() is incorrect");
    }
}

void test_string_name(const parameter_name& name)
{
    if( (name.has_long_name() == true && name.has_short_name() == true) ||
	name.has_long_name() == true )
    {
	if( name.string_name() != long_name )
	{
	    throw initialization_error("name.string_name() does not equal long name");
	}
    }
    else if( name.has_short_name() == true )
    {
	if( name.string_name() != short_name_str )
	{
	    throw initialization_error("name.string_name() does not equal short name");
	}
    }
}

int main(int argc, char** argv)
{
    parameter_name name1(long_name, short_name);
    parameter_name name2(long_name);
    parameter_name name3(short_name);

    try
    {
	test_long_name(name1);
	test_long_name(name2);

	test_short_name(name1);
	test_short_name(name3);

	test_string_name(name1);
	test_string_name(name2);
	test_string_name(name3);
    }
    catch(const initialization_error& ex)
    {
	cerr << ex.what() << endl;
	return 1;
    }

    return 0;
}
