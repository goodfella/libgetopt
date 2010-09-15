#!/bin/bash

NUMERIC_TESTS_DIR="$(dirname $0)/numeric-tests"

# numeric tests all run with no options
for test in $(ls -1 "${NUMERIC_TESTS_DIR}")
do
    if [ -x $(dirname $0)/numeric-tests/$test ]; then

	echo "running $test"
	${NUMERIC_TESTS_DIR}/$test
	TEST_STATUS="$?"

	if [ "$TEST_STATUS" -ne "0" ]; then
	    printf "%s FAILED with: %s\n" "$test" "$TEST_STATUS"
	    exit 1
	fi
    fi
done

echo "All tests PASSED"