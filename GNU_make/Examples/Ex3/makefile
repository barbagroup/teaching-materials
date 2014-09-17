#======================================================================
# Title: ex3
# Purpose: Variables (Macro)
#======================================================================
CC=gcc
CFLAGS=-g3 -Wall -pedantic-errors
OBJS=PrintHello.o main.o
BIN=ex3
INC=HaHa.h

.PHONY: clean

${BIN}: ${OBJS}
	${CC} ${CFLAGS} -o ${BIN} ${OBJS}
%.o: %.c ${INC}
	${CC} ${CFLAGS} -o $@ $< -c
clean:
	-@rm ${BIN} ${OBJS}

#=============================End of File==============================