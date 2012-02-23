INCLUDE("../unit-test-macros.cmake")

unit_test(option-arg-valid option_arg_valid.cc)
unit_test(option-visitor visitor.cc)
unit_test(option-initialization option_initialization.cc)
unit_test(option-arg-list option_arg_list.cc)
unit_test(option-arg-vector option_arg_vector.cc)
unit_test(option-arg-invalid option_arg_invalid.cc)
unit_test(option-set-arg option_set_arg.cc)
