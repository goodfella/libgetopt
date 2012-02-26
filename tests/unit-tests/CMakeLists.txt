INCLUDE("../test-macros.cmake")

GETOPT_TEST(option-initialization option_initialization.cc)
GETOPT_TEST(option-set-arg option_set_arg.cc)
GETOPT_TEST(custom-parser-set custom_parser_set.cc)
GETOPT_TEST(invalid-name invalid_name.cc)
GETOPT_TEST(name-comparison name_comparison.cc)
GETOPT_TEST(name-initialization name_initialization.cc)
