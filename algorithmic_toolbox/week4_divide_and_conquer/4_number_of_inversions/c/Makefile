SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

.PHONY: clean build run test

clean:
	rm -f main test

build:
	gcc -Wall -Wextra -pedantic -std=c11 -o main main.c inversions.c

run:
	./main <<< "5 2 3 9 2 9"

test:
	gcc -Wall -Wextra -pedantic -std=c11 -o test test.c inversions.c
	./test
