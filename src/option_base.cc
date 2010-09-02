#include "option_base.h"

using std::string;

using namespace libgetopt;

option_base::~option_base() {}

bool libgetopt::option_base::is_set() const
{
    return m_is_set;
}

int* libgetopt::option_base::flag_ptr()
{
    return NULL;
}
