CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = lru.o
DEPS = function.h commands.h structures.h

all: lru.exe

lru.exe: $(OBJ)
	$(CC) $(CFLAGS) -o lru.exe $(OBJ)


lru.o: lru.c $(DEPS)
	$(CC) $(CFLAGS) -c lru.c





clean:
	del /Q *.o main.exe

