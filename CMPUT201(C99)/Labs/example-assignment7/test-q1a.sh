#!/bin/bash
bash ./question1.sh > /dev/null 2> /dev/null
RET=$? # get the return code of your question1.sh
if [ $RET == 0 ];
then
    echo Program didn\'t crash
else
    if [[ $RET != 134  && $RET != 139 ]];
    then
        echo Unexpected return code of \!134/139 = $RET
    fi
fi

