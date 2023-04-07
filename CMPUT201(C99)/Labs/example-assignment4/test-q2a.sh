#!/bin/bash
bash ./question2.sh <q2a-test1-input.txt >q2a-test1-output.txt
diff -b q2a-test1-output.txt q2a-test1-expected-output.txt

bash ./question2.sh <q2a-test2-input.txt >q2a-test2-output.txt
diff -b q2a-test2-output.txt q2a-test2-expected-output.txt

bash ./question2.sh <q2a-test3-input.txt >q2a-test3-output.txt
diff -b q2a-test3-output.txt q2a-test3-expected-output.txt

bash ./question2.sh <q2a-test4-input.txt >q2a-test4-output.txt
diff -b q2a-test4-output.txt q2a-test4-expected-output.txt

bash ./question2.sh <q2a-test5-input.txt >q2a-test5-output.txt
diff -b q2a-test5-output.txt q2a-test5-expected-output.txt

bash ./question2.sh <q2a-test6-input.txt >q2a-test6-output.txt
diff -b q2a-test6-output.txt q2a-test6-expected-output.txt
