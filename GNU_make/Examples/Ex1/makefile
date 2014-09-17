#======================================================================
# Title: ex1
# Purpose: A Simplest Makefile
#======================================================================

ex1: PrintHello.o main.o
	gcc -g3 -Wall -pedantic-errors -o ex1 main.o PrintHello.o
PrintHello.o: PrintHello.c
	gcc -g3 -Wall -pedantic-errors -o PrintHello.o PrintHello.c -c
main.o: main.c HaHa.h
	gcc -g3 -Wall -pedantic-errors -o main.o main.c -c
clean:
	rm ex1 main.o PrintHello.oz

#=============================End of File==============================
