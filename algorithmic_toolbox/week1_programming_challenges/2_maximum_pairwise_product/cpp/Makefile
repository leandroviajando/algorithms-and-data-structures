SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

.PHONY: clean build run test

clean:
	rm -f main test

build:
	g++ -std=c++20 -Wall -Wextra -pedantic -o main main.cpp max_pairwise_product.cpp

run:
	./main <<< "3 1 2 3"

test:
	g++ -std=c++20 -Wall -Wextra -pedantic -o test test.cpp max_pairwise_product.cpp -pthread
	./test
