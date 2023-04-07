#!/bin/bash

bash ./question2-clang.sh <q2b-test1-input.txt >q2b-test1-output.txt
diff -b q2b-test1-output.txt q2b-test1-expected-output.txt

bash ./question2-clang.sh <q2b-test2-input.txt >q2b-test2-output.txt
diff -b q2b-test2-output.txt q2b-test2-expected-output.txt

