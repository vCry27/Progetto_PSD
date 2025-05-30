CC = gcc
CFLAGS = -Wall

OBJS = main.o attivita.o lista.o

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: main.c attivita.h lista.h
	$(CC) $(CFLAGS) -c main.c

attivita.o: attivita.c attivita.h
	$(CC) $(CFLAGS) -c attivita.c

lista.o: lista.c lista.h attivita.h
	$(CC) $(CFLAGS) -c lista.c

clean:
	rm -f *.o main run_test output.txt

test: run_test
	./run_test

run_test: run_test.c attivita.c lista.c attivita.h lista.h
	$(CC) $(CFLAGS) run_test.c attivita.c lista.c -o run_test
