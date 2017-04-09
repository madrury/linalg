all: linalg

linalg:
	gcc -std=c99 -Wall -g -O3 -o linalg -Wall main.c vector.c matrix.c errors.c util.c tests.c linsolve.c eigen.c linreg.c rand.c
