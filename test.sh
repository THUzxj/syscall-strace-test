#!/bin/bash

TESTS=$(ls src/)

for TEST in $TESTS ; do
    ./src/${TEST}/test.sh
done
