MAKEFLAGS = ks

main: main.c
	gcc -o main main.c -Ldlib/src -Idlib/src -ldlib -Lapue.3e/lib -Iapue.3e/include -lapue

run:
	# make ls
	# make ubio
	make runcmd
	# make ugid

ls:
	./main ls

ubio:
	./main ubio

runcmd:
	./main runcmd

ugid:
	./main ugid
