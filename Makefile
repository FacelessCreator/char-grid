.PHONY: all clear

all: build/main
	build/main

clear:
	rm -r build

build:
	mkdir -p build

build/char-grid.o: build src/char-grid.h src/char-grid.cpp
	g++ -g -c src/char-grid.cpp -o build/char-grid.o

build/tree.o: build src/tree.h src/tree.cpp
	g++ -g -c src/tree.cpp -o build/tree.o

build/main.o: build src/main.cpp
	g++ -g -c src/main.cpp -o build/main.o

build/main: build build/char-grid.o build/tree.o build/main.o
	g++ build/*.o -o build/main
