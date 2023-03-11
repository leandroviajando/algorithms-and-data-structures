SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

.PHONY: main test

main:
	g++ -std=c++11 -Wall -Wextra -pedantic -o main main.cpp max_pairwise_product.cpp
	echo 'Run the program with: ./main <<< "3 1 2 3"'

test:
	g++ -std=c++11 -Wall -Wextra -pedantic -o test test.cpp max_pairwise_product.cpp -pthread
	./test
