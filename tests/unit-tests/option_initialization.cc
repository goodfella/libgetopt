#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>

#include "libgetopt.h"

using namespace std;
using namespace libgetopt;

struct check_option : public unary_function<pair<option<parse_arg_passed>*, bool>, bool>
{
	bool operator() (const pair<option<parse_arg_passed>*,
			 bool>& opt_info) const;
};

int main(int argc, char** argv)
{
    vector<pair<option<parse_arg_passed>*, bool> > options;

    option<parse_arg_passed> required_arg1("opt");
    option<parse_arg_passed> required_arg2('o');
    option<parse_arg_passed> required_arg3("opt", 'o');

    option<parse_arg_passed> optional_arg1("opt", false);
    option<parse_arg_passed> optional_arg2('o', false);
    option<parse_arg_passed> optional_arg3("opt", 'o', false);

    options.push_back(make_pair(&required_arg1, true));
    options.push_back(make_pair(&required_arg2, true));
    options.push_back(make_pair(&required_arg3, true));

    options.push_back(make_pair(&optional_arg1, false));
    options.push_back(make_pair(&optional_arg2, false));
    options.push_back(make_pair(&optional_arg3, false));

    if( find_if(options.begin(),
		options.end(),
		not1(check_option())) != options.end() )
    {
	return 1;
    }

    return 0;
}

bool check_option::operator() (const pair<option<parse_arg_passed>*,
			       bool>& opt_info) const
{
    if( opt_info.first->present() == true )
    {
	cerr << "is_present is true before parsing\n";
	return false;
    }

    if( opt_info.first->arg_present() == true )
    {
	cerr << "arg_present is true before parsing\n";
	return false;
    }

    if( opt_info.first->arg_valid() == true )
    {
	cerr << "arg_valid is true before parsing\n";
	return false;
    }

    if( opt_info.first->arg_required() != opt_info.second )
    {
	cerr << "arg required is: " << opt_info.first->arg_required();
	cerr << " and should be: " << opt_info.second << endl;
	return false;
    }

    return true;
}
