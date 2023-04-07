#!/bin/bash
bash ./question1-clang.sh <q1a-test1-input.txt >q1a-test1-output.txt
diff -b q1a-test1-output.txt q1a-test1-expected-output.txt

bash ./question1-clang.sh <q1a-test2-input.txt >q1a-test2-output.txt
diff -b q1a-test2-output.txt q1a-test2-expected-output.txt

bash ./question1-clang.sh <q1a-test3-input.txt >q1a-test3-output.txt
diff -b q1a-test3-output.txt q1a-test3-expected-output.txt

bash ./question1-clang.sh <q1a-test4-input.txt >q1a-test4-output.txt
diff -b q1a-test4-output.txt q1a-test4-expected-output.txt

bash ./question1-clang.sh <q1a-test5-input.txt >q1a-test5-output.txt
diff -b q1a-test5-output.txt q1a-test5-expected-output.txt

bash ./question1-clang.sh <q1a-test6-input.txt >q1a-test6-output.txt
diff -b q1a-test6-output.txt q1a-test6-expected-output.txt
