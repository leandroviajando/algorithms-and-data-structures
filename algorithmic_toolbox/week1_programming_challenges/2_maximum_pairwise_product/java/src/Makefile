SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

.PHONY: clean build run test

clean:
	rm -f MaxPairwiseProduct.class

build:
	javac MaxPairwiseProduct.java

run:
	java MaxPairwiseProduct <<< "3 1 2 3"

test:
	javac MaxPairwiseProduct.java TestMaxPairwiseProduct.java
	java TestMaxPairwiseProduct
