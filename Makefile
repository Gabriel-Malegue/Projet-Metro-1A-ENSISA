CC = gcc
CFLAGS = -Wall -Wextra -Iheaders #-g -O0 #(pour tester les fuites de mémoire (merci Guillaume)) (valgrind --leak-check=full --track-origins=yes ./bin/metro.exe)
TARGET = bin/metro.exe

SRCS = main.c src/graph.c src/menu.c src/dico.c src/station.c src/trie.c src/dijkstra.c

all: | bin
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

bin:
	mkdir -p bin

clean:
	rm -f $(TARGET)