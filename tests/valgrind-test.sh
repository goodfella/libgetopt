#!/bin/bash

VALGRIND_LOG="${1}-valgrind.log"

printf "running valgrind on $1\n"
if ! valgrind --leak-check=full \
    --show-reachable=yes \
    --error-exitcode=1 \
    --log-file="${VALGRIND_LOG}" \
    $1; then

    echo "$1 valgrind test FAILED, details are in ${VALGRIND_LOG}"
    exit 1
else

    if grep -q 'LEAK SUMMARY' "${VALGRIND_LOG}"; then

	echo "$1 valgrind test FAILED details are in ${VALGRIND_LOG}"
	exit 1
    fi
fi

rm -f "${VALGRIND_LOG}"
exit 0
