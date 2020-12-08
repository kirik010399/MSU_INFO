all: main.o matrix.o solve.o
	g++ -pthread main.o matrix.o solve.o

main.o: main.cpp matrix.hpp solve.hpp 
	g++ main.cpp -c -o main.o

matrix.o: matrix.cpp matrix.hpp
	g++ matrix.cpp -c -o matrix.o

solve.o: solve.cpp solve.hpp
	g++ solve.cpp -c -o solve.o

clean:
	rm -f *.o
