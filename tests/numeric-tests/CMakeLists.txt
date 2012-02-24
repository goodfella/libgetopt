INCLUDE("../unit-test-macros.cmake")

unit_test(int-invalid int_invalid.cc)
unit_test(int-max int_max_arg.cc)
unit_test(int-min int_min_arg.cc)
unit_test(int-overflow int_overflow.cc)
unit_test(int-underflow int_underflow.cc)
