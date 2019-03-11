all: main.o matrixFunctions.o solvingFunctions.o
	gcc $^ -o program
main.o: main.c matrixFunctions.h solvingFunctions.h
	gcc -c $<
matrixFunctions.o: matrixFunctions.c matrixFunctions.h solvingFunctions.h
	gcc -c $<
solvingFunctions.o: solvingFunctions.c matrixFunctions.h solvingFunctions.h
	gcc -c $<
clean:
	rm -f *.o program