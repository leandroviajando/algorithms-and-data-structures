SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

.PHONY: clean build run test

clean:
	rm -f main test

build:
	gcc -Wall -Wextra -pedantic -std=c11 -o main main.c binary_search.c

run:
	./main <<< "5 1 5 8 12 13 5 8 1 23 1 11"

test:
	gcc -Wall -Wextra -pedantic -std=c11 -o test test.c binary_search.c
	./test
