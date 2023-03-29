SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

.PHONY: clean build run test

clean:
	rm -f main test

build:
	g++ -std=c++20 -Wall -Wextra -pedantic -o main main.cpp sorting.cpp

run:
	./main <<< "5 2 3 9 2 2"

test:
	g++ -std=c++20 -Wall -Wextra -pedantic -o test test.cpp sorting.cpp -pthread
	./test
