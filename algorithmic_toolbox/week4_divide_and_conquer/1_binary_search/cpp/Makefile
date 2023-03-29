SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

.PHONY: clean build run test

clean:
	rm -f main test

build:
	g++ -std=c++20 -Wall -Wextra -pedantic -o main main.cpp binary_search.cpp

run:
	./main <<< "5 1 5 8 12 13 5 8 1 23 1 11"

test:
	g++ -std=c++20 -Wall -Wextra -pedantic -o test test.cpp binary_search.cpp -pthread
	./test
