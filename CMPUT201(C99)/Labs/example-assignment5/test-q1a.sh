#!/bin/bash
bash ./question1.sh <q1a-test1-input.txt >q1a-test1-output.txt
diff -b q1a-test1-output.txt q1a-test1-expected-output.txt

bash ./question1.sh <q1a-test2-input.txt >q1a-test2-output.txt
diff -b q1a-test2-output.txt q1a-test2-expected-output.txt

