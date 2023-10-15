PROG = tictactoe
CC = gcc
CFLAGSLIBS = `pkg-config --cflags --libs gtk4`

${PROG}: main.o resources.o ${PROG}.o
		${CC} ${CFLAGSLIBS} -o ${PROG} build/resources.o build/${PROG}.o build/main.o

resources.o: src/resources.c
	${CC} ${CFLAGSLIBS} -o build/resources.o -c src/resources.c

${PROG}.o: src/${PROG}.c
	${CC} ${CFLAGSLIBS} -o build/${PROG}.o -c src/${PROG}.c

main.o: src/main.c
	${CC} ${CFLAGSLIBS} -o build/main.o -c src/main.c
	
clean:
	rm ${PROG} build/*.o
