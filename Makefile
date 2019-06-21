all: example

LinkedList.o: LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c

Example.o: LinkedList.h Example.c
	$(CC) $(CFLAGS) -c Example.c

Example: LinkedList.o Example.o
	$(CC) $(CFLAGS) -o example Example.o LinkedList.o

clean:
	rm -f *.o example