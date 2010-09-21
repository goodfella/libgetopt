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

NUMERIC_TESTS_DIR="$(dirname $0)/numeric-tests"
NUMERIC_TESTS="$(ls -1 ${NUMERIC_TESTS_DIR})"

printf "Running numeric tests:\n\n"

# numeric tests all run with no options
for test in ${NUMERIC_TESTS}
do
    if [ -x $(dirname $0)/numeric-tests/$test ]; then

	printf "\trunning $test\n"
	${NUMERIC_TESTS_DIR}/$test
	TEST_STATUS="$?"

	if [ "$TEST_STATUS" -ne "0" ]; then
	    printf "\t%s FAILED with: %s\n" "$test" "$TEST_STATUS"
	    exit 1
	fi
    fi
done

echo
printf "Running invalid-option test\n"
$(dirname $0)/invalid-option


echo
printf "Running valgrind tests:\n\n"

for test in ${NUMERIC_TESTS}
do
    TEST_PATH="${NUMERIC_TESTS_DIR}/${test}"

    if [ -x "${TEST_PATH}" ]; then

	VALGRIND_LOG="${test}-valgrind.log"
	if ! valgrind_test "${TEST_PATH}" "${VALGRIND_LOG}"; then
	    exit 1
	fi
    fi

done

valgrind_test "$(dirname $0)/invalid-option" "$(dirname $0)/invalid-option-valgrind.log"

echo
echo "valgrind tests passed"
echo

echo "All tests PASSED"