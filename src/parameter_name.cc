#include <algorithm>
#include <functional>
#include <limits>

#include "parameter_name.h"

using namespace libgetopt;
using std::string;

const string parameter_name::string_name() const
{
    if( has_long_name() == true )
    {
	return long_name();
    }
    else
    {
	return string(1, short_name());
    }
}

void parameter_name::check_name(const char short_name)
{
    if( bad_name_char(short_name) == true )
    {
	throw parameter_name::invalid_name("short option is not a graphical character");
    }
    else if( short_name == '-' )
    {
	throw parameter_name::invalid_name("short option cannot be '-'");
    }
}

void parameter_name::check_name(const string& long_name)
{
    if( long_name == "" )
    {
	throw parameter_name::invalid_name("long name is null");
    }
    else if( long_name[0] == '-' )
    {
	throw parameter_name::invalid_name("first character of long name cannot be a '-'");
    }

    string::const_iterator bad_chr = long_name.end();

    bad_chr = find_if(long_name.begin(), long_name.end(), bad_name_char);

    if( bad_chr != long_name.end() )
    {
	throw parameter_name::invalid_name("long name contains a non graphical character");
    }
}

bool operator==(const parameter_name& lhs, const int rhs)
{
    if( rhs > std::numeric_limits<char>::max() )
    {
	return false;
    }

    char temp = static_cast<char>(rhs);
    return temp == lhs.short_name();
}
