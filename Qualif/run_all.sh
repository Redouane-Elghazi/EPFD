#!/bin/bash

# Compile code
clang++ -O3 -Wall --std=c++14 main.cpp -o a.out

# Lunch tests
for file in `ls input`
do
	echo -e "\n\nfile: $file"
	time ./a.out input/$file > output/${file/.in/.out}
done
