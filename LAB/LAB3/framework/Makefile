hash: main.exe hashtable.o
main.exe: main.cpp hashtable.o
	g++ -O2 main.cpp hashtable.o -o main
hashtable.o: hashtable.cpp
	g++ hashtable.cpp -o hashtable.o -c
gen: gen.cpp
	g++ gen.cpp -o gen
	./gen 1 1 && ./gen 2 0.5 && ./gen 3 0
test: test.cpp
	g++ test.cpp -o test