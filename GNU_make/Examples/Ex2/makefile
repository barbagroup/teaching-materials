#======================================================================
# Title: ex2
# Purpose: Simple Imlicit Rule, PHONY, -, @, <@, @<
#======================================================================

.PHONY: clean
ex2: PrintHello.o main.o
	gcc -g3 -Wall -pedantic-errors -o ex2 main.o PrintHello.o
%.o:%.c HaHa.h
	gcc -g3 -Wall -pedantic-errors -o $@ $< -c
clean:
	-@rm ex2
	-@rm main.o
	-@rm PrintHello.o

#=============================End of File==============================