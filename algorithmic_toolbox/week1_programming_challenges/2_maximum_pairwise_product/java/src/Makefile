SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

.PHONY: main test

main:
	javac MaxPairwiseProduct.java
	echo 'Run the program with: java MaxPairwiseProduct <<< "3 1 2 3"'

test:
	javac MaxPairwiseProduct.java TestMaxPairwiseProduct.java
	java TestMaxPairwiseProduct
