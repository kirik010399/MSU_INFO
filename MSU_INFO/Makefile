program: main.o matrixUtils.o invertingManager.o
	g++ $^ -o program
main.o: main.cpp matrixUtils.hpp invertingManager.hpp
	g++ $<
matrixUtils.o: matrixUtils.cpp matrixUtils.hpp invertingManager.hpp
	g++ $<
invertingManager.o: invertingManager.cpp matrixUtils.hpp invertingManager.hpp
	g++ $<