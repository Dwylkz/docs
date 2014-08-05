CC = gcc
CFLAGS = -I../unpv13e/lib -g -O2 -D_REENTRANT -Wall
LIBS = ../unpv13e/libunp.a -lpthread

PROGS = $(subst .c,,$(wildcard *.c))

HOST = 127.0.0.1

all: $(PROGS)

.PHONY: run
run:
	./daytimetcpcli $(HOST)

.PHONY: clean
clean:
	rm -f $(PROGS)

%: %.c
	gcc $(CFLAGS) $< $(LIBS) -o $@
