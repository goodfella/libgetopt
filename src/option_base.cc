#include "option_base.h"

using std::string;

using namespace libgetopt;

option_base::~option_base() {}

int* libgetopt::option_base::flag_ptr()
{
    return NULL;
}
