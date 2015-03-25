MAKEFLAGS = ks

main: main.c
	gcc -o main main.c -Ldlib/src -Idlib/src -ldlib -Lapue.3e/lib -Iapue.3e/include -lapue

run:
	# make ls
	make ubio

ls:
	./main ls

ubio:
	./main ubio
