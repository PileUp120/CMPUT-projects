#!/bin/bash
bash ./question2.sh <q2a-test1-input.txt >q2a-test1-output.txt
diff -b q2a-test1-output.txt q2a-test1-expected-output.txt

bash ./question2.sh <q2a-test2-input.txt >q2a-test2-output.txt
diff -b q2a-test2-output.txt q2a-test2-expected-output.txt


bash ./question2.sh <q2a-test3-input.txt >q2a-test3-output.txt
diff -b q2a-test3-output.txt q2a-test3-expected-output.txt

