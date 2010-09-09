#include <algorithm>
#include <functional>

#include "option_base.h"

using std::string;

using namespace libgetopt;

const option_base::short_opt_predicate_t
option_base::short_opt_pred = &option_base::matches;

const option_base::long_opt_predicate_t
option_base::long_opt_pred = &option_base::matches;

const option_base::val_predicate_t
option_base::val_pred = &option_base::matches;

const option_base::duplicate_opt_predicate_t
option_base::duplicate_opt_pred = &option_base::matches;


option_base::~option_base() {}

int* libgetopt::option_base::flag_ptr()
{
    return NULL;
}

const string option_base::name() const
{
    string name;

    if( has_long_option() == true )
    {
	name = long_option();
    }
    else if( has_short_option() == true )
    {
	name += short_option();
    }

    return name;
}

void option_base::check_opt(const char short_opt)
{
    if( bad_char(short_opt) == true )
    {
	throw invalid_option("short option is not a graphical character");
    }
    else if( short_opt == '-' )
    {
	throw invalid_option("short option cannot be '-'");
    }
}

void option_base::check_opt(const string& long_opt)
{
    if( long_opt == "" )
    {
	throw invalid_option("long option is null");
    }
    else if( long_opt[0] == '-' )
    {
	throw invalid_option("first character of long option cannot be a '-'");
    }

    string::const_iterator bad_chr = long_opt.end();

    bad_chr = find_if(long_opt.begin(), long_opt.end(), bad_char);

    if( bad_chr != long_opt.end() )
    {
	throw invalid_option("long option contains a non graphical character");
    }
}

bool option_base::matches(option_base const * const opt) const
{
    bool match_found = false;

    if( opt->has_long_option() )
    {
	match_found = matches(opt->long_option().c_str());
    }

    if( match_found == true )
    {
	return true;
    }

    if( opt->has_short_option() )
    {
	match_found = matches(opt->short_option());
    }

    if( match_found == true )
    {
	return true;
    }

    return false;
}
