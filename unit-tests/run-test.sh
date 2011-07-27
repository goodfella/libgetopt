#!/bin/bash

# 1 = path to test

echo "running ${1}"
${1}
TEST_STATUS="$?"

if [ "$TEST_STATUS" -ne "0" ]; then
    echo test failed and returned $TEST_STATUS
    exit 1
fi

exit 0
