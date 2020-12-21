all: main.o matrix.o values.o
	g++ main.o matrix.o values.o

main.o: main.cpp matrix.hpp values.hpp 
	g++ main.cpp -c -o main.o

matrix.o: matrix.cpp matrix.hpp
	g++ matrix.cpp -c -o matrix.o

values.o: values.cpp values.hpp
	g++ values.cpp -c -o values.o

clean:
	rm -f *.o
