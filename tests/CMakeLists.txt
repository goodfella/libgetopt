# subdirectories all the unit test directories
PROJECT(unit-tests)
ADD_SUBDIRECTORY(parameter-name-tests)
ADD_SUBDIRECTORY(cmdline-parser-tests)
ADD_SUBDIRECTORY(option-tests)
ADD_SUBDIRECTORY(numeric-tests)
ADD_SUBDIRECTORY(custom-parser-tests)
ENABLE_TESTING()
