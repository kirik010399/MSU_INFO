all: main.o matrix.o invert.o
	mpicxx main.o matrix.o invert.o

main.o: main.cpp matrix.hpp invert.hpp 
	mpicxx main.cpp -c -o main.o

matrix.o: matrix.cpp matrix.hpp
	mpicxx matrix.cpp -c -o matrix.o

invert.o: invert.cpp invert.hpp
	mpicxx invert.cpp -c -o invert.o

clean:
	rm -f *.o
