ENABLE_TESTING()

MACRO(GETOPT_TEST name source)
  ADD_EXECUTABLE(${name} ${source})
  TARGET_LINK_LIBRARIES(${name} getopt unit-test)
  ADD_TEST(${name} ${name})
#  ADD_TEST(${name}-valgrind ${PROJECT_BINARY_DIR}/valgrind-test.sh ${CMAKE_CURRENT_BINARY_DIR}/${name})
ENDMACRO(GETOPT_TEST)
