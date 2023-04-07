#!/bin/bash
bash ./question6.sh $* <q6a-test1-input.txt >q6a-test1-output.txt
diff -b q6a-test1-output.txt q6a-test1-expected-output.txt
