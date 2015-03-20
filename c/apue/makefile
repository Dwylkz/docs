MAKEFLAGS = ks

main: main.c
	gcc -o main main.c -Ldlib/src -Idlib/src -ldlib

run:
	make ls

ls:
	./main ls
