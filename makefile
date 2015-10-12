all: linalg

linalg:
	gcc -std=c99 -g -o linalg -Wall main.c vector.c matrix.c errors.c util.c tests.c
