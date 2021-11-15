CC=g++

CFLAGS=-c -msse4.1
INCDIR=-I.

all: P1 P2

P1: P1.o 
	$(CC) P1.o -o P1

P2: P2.o 
	$(CC) P2.o -o P2

P1.o: P1.cpp
	$(CC) $(CFLAGS) $(INCDIR) P1.cpp

P2.o: P2.cpp
	$(CC) $(CFLAGS) $(INCDIR) P2.cpp

clean:
	rm -f *o P1 P2