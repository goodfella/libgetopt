#include "option_base.h"

using std::string;

using namespace libgetopt;

const option_base::short_opt_predicate_t
option_base::short_opt_pred = &option_base::matches;

const option_base::long_opt_predicate_t
option_base::long_opt_pred = &option_base::matches;

const option_base::val_predicate_t
option_base::val_pred = &option_base::matches;


option_base::~option_base() {}

int* libgetopt::option_base::flag_ptr()
{
    return NULL;
}

const string libgetopt::option_base::name() const
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
