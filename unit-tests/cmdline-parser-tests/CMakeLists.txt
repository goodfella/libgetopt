INCLUDE("../unit-test-macros.cmake")

unit_test(duplicate-option duplicate_option.cc)
unit_test(invalid-option invalid_option.cc)
unit_test(option-invalid option_invalid_arg.cc)
unit_test(option-missing option_missing_arg.cc)
unit_test(option-valid-arg option_valid_arg.cc)
unit_test(parser-in-use parser_in_use.cc)
unit_test(cmdline-visitor visitor.cc)
