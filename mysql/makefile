CC = gcc
CFLAGS = -lmysqlclient -O2 $(mysql_config --cflags)

main: main.c

.PHONY: run
run:
	./main

.PHONY: clean
clean:
	rm -f main
