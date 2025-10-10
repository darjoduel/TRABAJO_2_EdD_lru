TARGET = main.exe
SRC = $(wildcard *.c)
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -mconsole

all: $(TARGET)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	del /Q $(TARGET) 2>nul || true

run: $(TARGET)
	.\$(TARGET)
