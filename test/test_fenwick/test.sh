#!/bin/bash
mkdir tmp
cd tmp
g++ ../../../data_structures/fenwick.cpp -fsanitize=undefined -fsanitize=address -o fenwick
g++ ../../test_RMQ/stupid.cpp -o stupid
g++ ../../test_RMQ/gen.cpp -o gen

for (( i = 0; i < 100; i++ )) do
	./gen 1000 1000 > input
	./fenwick < input > out1
	./stupid < input > out2 
	if diff "out1" "out2" &> /dev/null -eq 0; then
		echo "input:"
		cat input 
		echo "wrong:"
		cat out1
		echo "correct:"
		cat out2
		exit
	fi
done
echo "tests 1000 1000 passed"

for (( i = 0; i < 100; i++ )) do
	./gen 10000 10000 > input
	./fenwick < input > out1
	./stupid < input > out2 
	if diff "out1" "out2" &> /dev/null -eq 0; then
		echo "input:"
		cat input 
		echo "wrong:"
		cat out1
		echo "correct:"
		cat out2
		exit
	fi
done
echo "tests 10000 10000 passed"

cd ..
rm -rf tmp
echo "all tests passed"