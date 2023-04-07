#!/bin/bash
bash ./question3-clang.sh $* <q3a-test1-input.txt >q3a-test1-output.txt
diff -b q3a-test1-output.txt q3a-test1-expected-output.txt

bash ./question3-clang.sh $* <q3a-test2-input.txt >q3a-test2-output.txt
diff -b q3a-test2-output.txt q3a-test2-expected-output.txt

