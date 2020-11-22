all: main.o matrix.o invert.o
	g++ -lpthread main.o matrix.o invert.o

main.o: main.cpp matrix.hpp invert.hpp 
	g++ main.cpp -c -o main.o

matrix.o: matrix.cpp matrix.hpp
	g++ matrix.cpp -c -o matrix.o

invert.o: invert.cpp invert.hpp
	g++ invert.cpp -c -o invert.o

clean:
	rm -f *.o
