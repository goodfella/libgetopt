#!/bin/bash

NUMERIC_TESTS_DIR="$(dirname $0)/numeric-tests"

printf "Running numeric tests:\n\n"

# numeric tests all run with no options
for test in $(ls -1 "${NUMERIC_TESTS_DIR}")
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
echo "All tests PASSED"