PROG = tictactoe
CC = gcc
CFLAGS =`pkg-config --cflags gtk4`
LIBS = `pkg-config --libs gtk4`

${PROG}: main.o resources.o ${PROG}.o
		${CC} ${CFLAGS} -o ${PROG} build/resources.o build/${PROG}.o build/main.o ${LIBS}

resources.o: src/resources.c
	${CC} `pkg-config --cflags gio-2.0` -o build/resources.o -c src/resources.c `pkg-config --libs gio-2.0`

${PROG}.o: src/${PROG}.c
	${CC} ${CFLAGS} -o build/${PROG}.o -c src/${PROG}.c ${LIBS}

main.o: src/main.c
	${CC} ${CFLAGS} -o build/main.o -c src/main.c ${LIBS}

clean:
	rm ${PROG} build/*.o
