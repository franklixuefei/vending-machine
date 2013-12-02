#!/bin/bash

numtests=50000
u++ main.cc &> /dev/null
make &> /dev/null
echo "test started... will run ${numtests} tests"
counter=0
for (( k = 1; k < ${numtests}; k++ )); do
    ./a.out > currentConfigFile.txt
    ./soda currentConfigFile.txt ${k} &> result.txt
    if [ $? -ne 0 ]; then
        echo "test failed with seed ${k}"
        exit 1;
    fi
    echo "current seed: ${k}" > seed.txt
    x=`egrep -ci "***********************" result.txt`;
    y=`egrep -ci "assertion" result.txt`;
    z=`egrep -ci "deadlock" result.txt`;
    if [ ${x} -eq 0 ] || [ ${y} -ne 0 ] || [ ${z} -ne 0 ]; then
        echo "test failed with seed ${k}"
        exit 1;
    fi
    counter=$((${counter}+1))
    if [ $((${counter} % 5000)) -eq 0 ]; then
        echo "${counter} tests run"
    fi	
done
echo "all tests passed!"
make clean &> /dev/null
exit 0
