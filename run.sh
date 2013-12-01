#!/bin/bash

set -e

for (( i = 0; i < 10000; i++ )); do

 ./a.out >test.config;
 echo "----------------------------------------"
 cat test.config;
 echo "----------------------------------------"
 ./soda test.config
  
done




