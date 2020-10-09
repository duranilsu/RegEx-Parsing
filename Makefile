CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror
PROGRAMS=rexp

programs: $(PROGRAMS)

rexp: main.o RecursiveParser.o convertToExpression.o tableDrivenParser.o
	$(CC) -o $@ $(CFLAGS) $^

clean:
	-rm *.o rexp
	-rm -r *dSYM

