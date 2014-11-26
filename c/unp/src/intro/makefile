CC = gcc
CFLAGS = -I../unpv13e/lib -Idlib/src -g -O2 -D_REENTRANT -Wall
LIBS = ../unpv13e/libunp.a -lpthread dlib/src/libdlib.a

PROGS = $(subst .c,,$(wildcard *.c))

HOST = 127.0.0.1

all: $(PROGS)

run:
	@#./daytimetcpcli $(HOST)
	@./main basic
	@#./main daytimetcpcli $(HOST)
	@./main daytimetcpcliv6 '::1'

clean:
	rm -f $(PROGS)

%: %.c
	gcc $(CFLAGS) $< $(LIBS) -o $@

.PHONY: run clean
