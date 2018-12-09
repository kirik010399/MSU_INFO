program: main.o matrixUtils.o solvingManager.o
	g++ -lpthread $^ -o program
main.o: main.cpp matrixUtils.hpp solvingManager.hpp
	g++ -c $<
matrixUtils.o: matrixUtils.cpp matrixUtils.hpp solvingManager.hpp
	g++ -c $<
solvingManager.o: solvingManager.cpp matrixUtils.hpp solvingManager.hpp
	g++ -c $<