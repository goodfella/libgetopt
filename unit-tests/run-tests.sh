#!/bin/bash

# 1 = binary path
# 2 = log path
function valgrind_test
{
    printf "\trunning valgrind on $1\n"
    if ! valgrind --leak-check=full \
	--show-reachable=yes \
	--error-exitcode=1 \
	--log-file="$2" \
	$1; then

	printf "\t%s valgrind test FAILED, details are in %s\n" "$test" "$2"
	return 1
    else

	if grep -q 'LEAK SUMMARY' "$2"; then

	    printf "\t%s valgrind test FAILED details are in %s\n" "$test" "$2"
	    return 1
	fi
    fi

    rm -f "${2}"
    return 0
}

# 1 = list of test names
function valgrind_tests
{
    for test in $1
    do
	if [ -x "${test}" ]; then

	    local VALGRIND_LOG="${test}-valgrind.log"
	    if ! valgrind_test "${test}" "${VALGRIND_LOG}"; then
		exit 1
	    fi
	fi

    done
}

# 1 = test path
# 2 = return val
function test_failed
{
    printf "\t%s FAILED with: %s\n" "$1" "$2"
    exit 1
}

# 1 = list of test names
function run_tests
{
    for test in $1
    do
	if [ -x "${test}" ]; then
	    printf "\trunning ${test}\n"
	    "${test}"
	    local TEST_STATUS="$?"

	    if [ "$TEST_STATUS" -ne "0" ]; then
		test_failed "${test}" "${TEST_STATUS}"
	    fi
	fi
    done
}

# 1 = test dir under unit-tests dir
function get_tests
{
    find $(dirname $0)/${1} -maxdepth 1 -perm -u+x -a -type f | grep -v "$(basename $0)"
}

NUMERIC_TESTS="$(get_tests numeric-tests)"
printf "Running numeric tests:\n\n"
run_tests "${NUMERIC_TESTS}"
echo

EXCEPTION_TESTS="$(get_tests exception-tests)"
printf "Running exception tests:\n\n"
run_tests "${EXCEPTION_TESTS}"
echo

OPTION_TESTS="$(get_tests option-tests)"
printf "Running option tests:\n\n"
run_tests "${OPTION_TESTS}"
echo

CMDLINE_PARSER_TESTS="$(get_tests cmdline-parser-tests)"
printf "Running cmdline parser tests:\n\n"
run_tests "${CMDLINE_PARSER_TESTS}"
echo

PARAMETER_NAME_TESTS="$(get_tests parameter-name-tests)"
printf "Running parameter name tests:\n\n"
run_tests "${PARAMETER_NAME_TESTS}"
echo

CUSTOM_PARSER_TESTS="$(get_tests custom-parser-tests)"
printf "Running custom parser tests:\n\n"
run_tests "${CUSTOM_PARSER_TESTS}"
echo


printf "Running valgrind tests:\n\n"
valgrind_tests "${NUMERIC_TESTS}"
valgrind_tests "${EXCEPTION_TESTS}"
valgrind_tests "${OPTION_TESTS}"
valgrind_tests "${CMDLINE_PARSER_TESTS}"
valgrind_tests "${PARAMETER_NAME_TESTS}"
valgrind_tests "${CUSTOM_PARSER_TESTS}"
echo

echo "valgrind tests passed"
echo

echo "All tests PASSED"
