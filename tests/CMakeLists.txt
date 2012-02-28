# subdirectories all the unit test directories
PROJECT(tests)

FIND_PROGRAM(VALGRIND valgrind)
FILE(COPY valgrind-test.sh DESTINATION ${PROJECT_BINARY_DIR}/)
IF(NOT VALGRIND)
  MESSAGE(STATUS "Install valgrind to enable the valgrind tests")
ENDIF()

ADD_SUBDIRECTORY(unit-tests)
ADD_SUBDIRECTORY(integration-tests)
ENABLE_TESTING()
