CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address -g
objects = vector.o bigint.o

all: $(objects)
	$(CC) $^ -o objects
	
testhash: data.o linked_list.o hash.o main.o
	$(CC) -fsanitize=address -o testhash data.o linked_list.o hash.o main.o -lm

testlinkedlist: data.o linked_list.o main.o
	$(CC) -fsanitize=address -o testlinkedlist data.o linked_list.o main.o -lm

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

%.c:
	touch $@

clean:
	rm -f *.o all