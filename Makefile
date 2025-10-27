CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address -g
objects = vector.o bigint.o

all: $(objects)
	$(CC) $^ -o objects
	
testhash: Data.o linked_list.o hash.o main.o
	$(CC) -fsanitize=address -o testhash Data.o hash.o main.o -lm

testlinkedlist: Data.o linked_list.o main.o
	$(CC) -fsanitize=address -o testlinkedlist Data.o linked_list.o main.o -lm

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

%.c:
	touch $@

clean:
	rm -f *.o all