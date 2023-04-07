#!/bin/bash
bash ./question4.sh $* <q4a-test1-input.txt >q4a-test1-output.txt
diff -b q4a-test1-output.txt q4a-test1-expected-output.txt
