program: main.o MatFun.o SolvHead.o
	g++ -lpthread $^ -o program
main.o: main.cpp MatFun.hpp SolvHead.hpp
	g++ -c $<
MatFun.o: MatFun.cpp MatFun.hpp SolvHead.hpp
	g++ -c $<
SolvHead.o: SolvHead.cpp MatFun.hpp SolvHead.hpp
	g++ -c $<