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
