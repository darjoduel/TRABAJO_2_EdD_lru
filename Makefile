# Makefile portable para LRU
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = lru

all: $(TARGET)

$(TARGET): lru.c
	$(CC) $(CFLAGS) -o $(TARGET) lru.c

clean:
	del /f /q $(TARGET).exe 2>nul || rm -f $(TARGET)

.PHONY: all clean
# Makefile portable para LRU
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = lru

all: $(TARGET)

$(TARGET): lru.c
	$(CC) $(CFLAGS) -o $(TARGET) lru.c

clean:
	rm -f $(TARGET).exe $(TARGET) $(TARGET).o lru.o

.PHONY: all clean
