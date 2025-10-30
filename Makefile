CC = gcc
CFLAGS = -Wall  -Wextra  -g
objects = vector.o bigint.o

all: $(objects)
	$(CC) $^ -o objects

testlinkedlist: data.o linked_list.o main.o
	$(CC) -fsanitize=address -o testlinkedlist data.o linked_list.o main.o -lm
	
testhash: data.o linked_list.o hash.o main.o
	$(CC) -o testhash data.o linked_list.o hash.o main.o -lm

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

%.c:
	touch $@

clean:
	rm -f *.o all