CC = clang
CFLAGS = -g

OBJ = grammar.o f1wae.o main.o

all: leg main

main: grammar.c ${OBJ}
	${CC} ${CFLAGS} ${OBJ}

grammar.c: grammar.leg
	../tools/peg/leg grammar.leg > grammar.c

leg:
	${MAKE} -C ../tools/peg leg

rebuild: clean all

clean:
	rm -f a.out ${OBJ}
	rm -f grammar.c

.PHONY: clean rebuild
