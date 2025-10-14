CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o
DEPS = function.h commands.h structures.h

all: main.exe

main.exe: $(OBJ)
	$(CC) $(CFLAGS) -o main.exe $(OBJ)


main.o: main.c $(DEPS)
	$(CC) $(CFLAGS) -c main.c





clean:
	del /Q *.o main.exe

