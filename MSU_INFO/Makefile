program: main.o matrixUtils.o invertingManager.o
	g++ -lpthread $^ -o program
main.o: main.cpp matrixUtils.hpp invertingManager.hpp
	g++ -c $<
matrixUtils.o: matrixUtils.cpp matrixUtils.hpp invertingManager.hpp
	g++ -c $<
invertingManager.o: invertingManager.cpp matrixUtils.hpp invertingManager.hpp
	g++ -c $<