all: linalg

linalg:
	gcc -std=c99 -o linalg -Wall main.c vector.c
