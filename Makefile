CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address -g
objects = vector.o bigint.o

all: $(objects)
	$(CC) $^ -o objects
	
testhash: hash.o main.o
	$(CC) -fsanitize=address -o testhash hash.o main.o -lm

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

%.c:
	touch $@

clean:
	rm -f *.o all