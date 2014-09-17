#======================================================================
# Title: ex4
# Purpose: A Simple Application
#======================================================================

CC = gcc

SRC = src
BPATH = bin
OPATH = obj
IPATH = includes

BIN = ex4
OBJ = PrintHello.o main.o
INC = HaHa.h

.PHONY: clean debug release build

debug: MODE = Debug
debug: CFLAGS = -g3 -Wall -pedantic-errors -I ${IPATH}
debug: 
	make build MODE="${MODE}" CFLAGS="${CFLAGS}"

release: MODE = Release
release: CFLAGS = -O3 -fopenmp -I ${IPATH}
release: 
	make build MODE="${MODE}" CFLAGS="${CFLAGS}"

build: 
	@if [ ! -e ${BPATH} ]; then mkdir ${BPATH}; fi
	@if [ ! -e ${BPATH}/${MODE} ]; then mkdir ${BPATH}/${MODE}; fi
	@if [ ! -e ${OPATH} ]; then mkdir ${OPATH}; fi
	make ${BPATH}/${MODE}/${BIN}

${BPATH}/${MODE}/${BIN}: $(foreach i, ${OBJ}, ${OPATH}/${i})
	${CC} ${CFLAGS} -o ${BPATH}/${MODE}/${BIN} \
				$(foreach i, ${OBJ}, ${OPATH}/${i})

${OPATH}/%.o: ${SRC}/%.c ${IPATH}/${INC}
	${CC} ${CFLAGS} -o $@ -c $<

clean:
	-@if [ -e ${BPATH} ]; then rm -r ${BPATH}; fi
	-@if [ -e ${OPATH} ]; then rm -r ${OPATH}; fi

#=============================End of File==============================