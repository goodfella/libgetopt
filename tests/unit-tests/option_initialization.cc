#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>

#include "libgetopt.h"

using namespace std;
using namespace libgetopt;

struct check_option : public unary_function<pair<option<parse_arg_passed>*, option_base::arg_policy_t>, bool>
{
	bool operator() (const pair<option<parse_arg_passed>*,
				    option_base::arg_policy_t>& opt_info) const;
};

int main(int argc, char** argv)
{
    vector<pair<option<parse_arg_passed>*, arg_parser::arg_policy_t> > options;

    option<parse_arg_passed> required_arg1("required1");
    option<parse_arg_passed> required_arg2('r');
    option<parse_arg_passed> required_arg3("required2", 'r');

    option<parse_arg_passed> optional_arg1("optional1", false);
    option<parse_arg_passed> optional_arg2('o', false);
    option<parse_arg_passed> optional_arg3("optional3", 'o', false);

    options.push_back(make_pair(&required_arg1, arg_parser::arg_required));
    options.push_back(make_pair(&required_arg2, arg_parser::arg_required));
    options.push_back(make_pair(&required_arg3, arg_parser::arg_required));

    options.push_back(make_pair(&optional_arg1, arg_parser::arg_optional));
    options.push_back(make_pair(&optional_arg2, arg_parser::arg_optional));
    options.push_back(make_pair(&optional_arg3, arg_parser::arg_optional));

    if( find_if(options.begin(),
		options.end(),
		not1(check_option())) != options.end() )
    {
	return 1;
    }

    return 0;
}

bool check_option::operator() (const pair<option<parse_arg_passed>*,
					  arg_parser::arg_policy_t>& opt_info) const
{
    if( opt_info.first->present() == true )
    {
	cerr << opt_info.first->name().string_name() << " is_present is true before parsing\n";
	return false;
    }

    if( opt_info.first->arg_present() == true )
    {
	cerr << opt_info.first->name().string_name() << " arg_present is true before parsing\n";
	return false;
    }

    if( opt_info.first->arg_valid() == true )
    {
	cerr << opt_info.first->name().string_name() << " arg_valid is true before parsing\n";
	return false;
    }

    if( opt_info.first->arg_policy() != opt_info.second )
    {
	cerr << opt_info.first->name().string_name() << " arg setting is: " << opt_info.first->arg_policy();
	cerr << " and should be: " << opt_info.second << endl;
	return false;
    }

    return true;
}
