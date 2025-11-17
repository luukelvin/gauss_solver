test : build/tests
	build/tests

build/tests : build/tests.o build/Solver.o build/Matrix.o build/utils.o
	g++ build/tests.o build/Solver.o build/Matrix.o build/utils.o -o build/tests

build/tests.o : src/tests.cpp build/Solver.o build/Matrix.o
	g++ -c src/tests.cpp -o build/tests.o

build/Solver.o : src/Solver.cpp src/utils.h src/Matrix.h src/Solver.h
	g++ -c src/Solver.cpp -o build/Solver.o

build/Matrix.o : src/Matrix.cpp src/Matrix.h src/utils.h
	g++ -c src/Matrix.cpp -o build/Matrix.o

build/utils.o : src/utils.cpp src/utils.h
	g++ -c src/utils.cpp -o build/utils.o
