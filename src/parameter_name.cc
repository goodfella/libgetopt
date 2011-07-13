#include <algorithm>
#include <functional>
#include <limits>

#include "parameter_name.h"

using namespace libgetopt;
using std::string;
using std::numeric_limits;

bool libgetopt::operator==(const parameter_name& lhs, const parameter_name& rhs)
{
    bool short_test =
	((lhs.has_short_name() == true) &&
	 (rhs.has_short_name() == true) &&
	 (lhs.short_name() == rhs.short_name()));

    bool long_test =
	((lhs.has_long_name() == true) &&
	 (rhs.has_long_name() == true) &&
	 (lhs.long_name() == rhs.long_name()));

    return (short_test || long_test);
}

bool libgetopt::operator==(const parameter_name& lhs, const char rhs)
{
    if( lhs.has_short_name() == true )
    {
	return lhs.short_name() == rhs;
    }
    else
    {
	return false;
    }
}

bool libgetopt::operator==(const parameter_name& lhs, const int rhs)
{
    if( rhs > numeric_limits<char>::max() || rhs < numeric_limits<char>::min() )
    {
	return false;
    }

    return lhs == static_cast<char>(rhs);
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
