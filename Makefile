CC = gcc
CFLAGS = -Wall -Wextra -Iheaders
DEBUGFLAGS = -g -O0
TARGET = bin/metro.exe

SRCS = main.c src/graph.c src/menu.c src/dico.c src/station.c src/trie.c src/dijkstra.c

all: | bin
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

bin:
	mkdir -p bin

clean:
	rm -f $(TARGET)

debug: CFLAGS += $(DEBUGFLAGS)
debug: clean all
valgrind: debug
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all $(TARGET)