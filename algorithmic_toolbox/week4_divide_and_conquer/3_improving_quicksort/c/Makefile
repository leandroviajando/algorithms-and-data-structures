SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

.PHONY: clean build run test

clean:
	rm -f main test

build:
	gcc -Wall -Wextra -pedantic -std=c11 -o main main.c sorting.c

run:
	./main <<< "5 2 3 9 2 2"

test:
	gcc -Wall -Wextra -pedantic -std=c11 -o test test.c sorting.c
	./test
