program: main.o matrixUtils.o calculatingManager.o
	g++ $^ -o program
main.o: main.cpp matrixUtils.hpp calculatingManager.hpp
	g++ -c $<
matrixUtils.o: matrixUtils.cpp matrixUtils.hpp calculatingManager.hpp
	g++ -c $<
calculatingManager.o: calculatingManager.cpp matrixUtils.hpp calculatingManager.hpp
	g++ -c $<