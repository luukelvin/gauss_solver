test : build/tests
	build/tests

build/tests : build/tests.o build/LinearSystem.o build/utils.o build
	g++ build/tests.o build/LinearSystem.o build/utils.o -o build/tests

build/tests.o : src/tests.cpp build/LinearSystem.o build
	g++ -c src/tests.cpp -o build/tests.o

build/LinearSystem.o : src/LinearSystem.cpp src/LinearSystem.h src/utils.h build
	g++ -c src/LinearSystem.cpp -o build/LinearSystem.o

build/utils.o : src/utils.cpp src/utils.h build
	g++ -c src/utils.cpp -o build/utils.o

build :
	mkdir build
