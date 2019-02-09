CC = gcc
CFLAGS = -Wall -g -std=c11


main: Sudoku.o
	$(CC) -shared -o Sudoku.dylib Sudoku.o
Sudoku.o: Sudoku.c
	$(CC) $(CFLAGS) -c -fpic Sudoku.c -o Sudoku.o
clean:
	@rm *.o Sudoku