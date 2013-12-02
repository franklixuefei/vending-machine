#!/bin/bash

echo "SCRIPT INT STARTED"
counter=0
for k in {1..100000}; do
    ./soda soda.config ${k} &> result.txt
            
    y=`egrep -ci "assertion" result.txt`;

    z=`egrep -ci "deadlock" result.txt`;

    if [ ${y} -ne 0 ] || [ ${z} -ne 0 ]; then
    echo "test failed"
         exit 1;
    fi
    counter=$((${counter}+1))
    #if [ $((${counter} % 5)) -eq 0 ]; then
    echo "passed ${counter}"
    # fi
done
echo "ALL TEST SUCCESSFULLY PASSED!"
make clean &> /dev/null
exit 0
