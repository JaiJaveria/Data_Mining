main: main.cpp
	gcc main.cpp -o main -lstdc++ -std=c++11

execute: main
	./main ../testdat.txt 40 output.txt
	diff correct_output/output_testdat.txt output.txt
	echo "testdat passed"
	./main ../output20.txt 10 output.txt
	diff correct_output/output_output20.txt output.txt
	echo "output20 passed"
mytest:	
	g++ test.cpp -o test
	./test input3 40
clear: 
	rm test




mytest1:	
	g++ test1.cpp -o test1
	./test1 input input1
	rm test1
cleartest1: 
	rm test1

mytest2:	
	g++ test2.cpp -o test2
	./test2
cleartest2: 
	rm test2

