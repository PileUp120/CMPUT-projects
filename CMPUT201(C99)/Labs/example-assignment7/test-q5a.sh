#!/bin/bash
bash ./question5.sh $* <q5a-test1-input.txt >q5a-test1-output.txt
diff -b q5a-test1-output.txt q5a-test1-expected-output.txt

bash ./question5.sh $* <q5a-test2-input.txt >q5a-test2-output.txt
diff -b q5a-test2-output.txt q5a-test2-expected-output.txt

