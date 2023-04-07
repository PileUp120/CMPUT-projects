#!/bin/bash
bash ./question7.sh $* <q7a-test1-input.txt >q7a-test1-output.txt
diff -b q7a-test1-output.txt q7a-test1-expected-output.txt   > q7a-test1-1-ouput.diff ||
diff -b q7a-test1-output.txt q7a-test1-expected-output-2.txt > q7a-test1-2-ouput.diff
if [ $? -ne 0 ];
then
    echo "The output didn't match"
    echo -e "\n\nq7a-test1-expected-output.txt\n\n"
    cat q7a-test1-1-ouput.diff || echo no diff
    echo -e "\n\nq7a-test1-expected-output-2.txt\n\n"
    cat q7a-test1-2-ouput.diff || echo no diff
    exit 1
fi

