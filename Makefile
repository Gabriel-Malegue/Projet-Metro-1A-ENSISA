CC = gcc
CFLAGS = -Wall -Wextra -Iheaders
TARGET = bin/metro.exe

SRCS = main.c src/graph.c src/menu.c src/dico.c

all: | bin
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

bin:
	mkdir -p bin

clean:
	rm -f $(TARGET)