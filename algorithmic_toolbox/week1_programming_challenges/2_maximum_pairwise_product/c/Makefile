SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

.PHONY: clean build run test

clean:
	rm -f main test

build:
	gcc -Wall -Wextra -pedantic -std=c11 -o main main.c max_pairwise_product.c

run:
	./main <<< "3 1 2 3"

test:
	gcc -Wall -Wextra -pedantic -std=c11 -o test test.c max_pairwise_product.c
	./test
