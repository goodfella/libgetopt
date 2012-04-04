CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(libgetopt CXX)
INCLUDE_DIRECTORIES(include libunit-test)

ADD_DEFINITIONS(-g)

SET(GETOPT_SOURCES
  src/option_list.cc
  src/cmdline_parser.cc
  src/strtonum.cc
  src/libgetopt_limits.cc
  src/option_base.cc
  src/arg_parser.cc
  src/named_parameter.cc
  src/parameter_name.cc
  src/cmdline_lexer.cc)
  
SET(UNIT_TEST_SOURCES
  libunit-test/unit_test.cc
  libunit-test/cmdline_args.cc)

ADD_LIBRARY(getopt STATIC ${GETOPT_SOURCES})
ADD_LIBRARY(unit-test ${UNIT_TEST_SOURCES})

ADD_SUBDIRECTORY(tests)
ENABLE_TESTING()
