all: linalg

linalg:
	gcc -std=c99 -Wall -g -o linalg -Wall main.c vector.c matrix.c errors.c util.c tests.c
