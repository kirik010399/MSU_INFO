all: main.o matrixUtils.o invertingManager.o
	g++ main.o matrixUtils.o invertingManager.o -lm -o App -O2

main.o: main.cpp invertingManager.hpp matrixUtils.hpp
	g++ main.cpp -c -o main.o -O2

matrixUtils.o: matrixUtils.cpp matrixUtils.hpp
	g++ matrixUtils.cpp -c -o matrixUtils.o -O2

invertingManager.o: invertingManager.cpp invertingManager.hpp
	g++ invertingManager.cpp -c -o invertingManager.o -O2

clean:
	rm -f *.o App
