# compiler
CC=gcc
# compiler flags
CFLAGS=-Wall -ansi -pedantic-errors
# link/load flags ex: "-lm" for math.h
LDFLAGS=

main:
	$(CC) $(CFLAGS) $(LDFLAGS) e2448199_the1.c -o e2448199_the1

prot:
	$(CC) $(CFLAGS) $(LDFLAGS) prototype.c -o prototype

clean:
	rm -rf e2448199_the1 prototype

run:
	./e2448199_the1 < input.txt > output.txt

run_prot:
	./prototype < input.txt > output.txt
	
all:
	rm -rf e2448199_the1 prototype
	sleep 1.5
	$(CC) $(CFLAGS) $(LDFLAGS) e2448199_the1.c -o e2448199_the1
	sleep 1
	clear
	./e2448199_the1 < input.txt > output.txt