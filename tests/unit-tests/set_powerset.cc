#include <iostream>
#include <string>

#include "set.h"

using namespace std;
using namespace libgetopt;
using namespace libgetopt::unit_tests;

typedef set<string> set_t;

int main(int argc, char ** argv)
{
	set_t s;

	for( int i = 1; i < argc; ++i)
	{
		s.add_element(argv[i]);
	}

	set_t::powerset_t powerset = set_t::powerset(s);

	for(set_t::powerset_iterator subset = powerset.begin();
	    subset != powerset.end();
	    ++subset)
	{
		for(set_t::iterator element = subset->begin();
		    element != subset->end();
		    ++element)
		{
			cout << *element << ' ';
		}

		cout << endl;
	}

	return 0;
}
