#!/bin/bash
bash ./question1-clang.sh <q1b-test1-input.txt >q1b-test1-output.txt
diff -b q1b-test1-output.txt q1b-test1-expected-output.txt

bash ./question1-clang.sh <q1b-test2-input.txt >q1b-test2-output.txt
diff -b q1b-test2-output.txt q1b-test2-expected-output.txt

bash ./question1-clang.sh <q1b-test3-input.txt >q1b-test3-output.txt
diff -b q1b-test3-output.txt q1b-test3-expected-output.txt

bash ./question1-clang.sh <q1b-test4-input.txt >q1b-test4-output.txt
diff -b q1b-test4-output.txt q1b-test4-expected-output.txt

bash ./question1-clang.sh <q1b-test5-input.txt >q1b-test5-output.txt
diff -b q1b-test5-output.txt q1b-test5-expected-output.txt

bash ./question1-clang.sh <q1b-test6-input.txt >q1b-test6-output.txt
diff -b q1b-test6-output.txt q1b-test6-expected-output.txt
