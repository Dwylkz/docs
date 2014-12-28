CC = gcc
CFLAGS = -I../unpv13e/lib -Idlib/src -g -O2 -D_REENTRANT -Wall
LIBS = ../unpv13e/libunp.a -lpthread dlib/src/libdlib.a

HOST = 127.0.0.1
HOST6 = ::1

all:
	make -C dlib/src
	make main

main: main.c

run:
	@#./daytimetcpcli $(HOST)
	@#./main basic
	@./main daytimetcpcli $(HOST)
	@#./main daytimetcpcliv6 $(HOST6)
	@#./main byteorder
	@#./main bytemanipulation
	@#./main inet_conv

srv:
	@#./main daytimetcpsrv
	@./main tcpserv01

cli:
	@./main tcpcli01 $(HOST) 0

test:
	@#./main multireq 10 $(HOST)
	@echo "test" | ./main tcpcli01test 10 $(HOST) 1

clean:
	rm -f $(PROGS)

%: %.c
	gcc $(CFLAGS) $< $(LIBS) -o $@

.PHONY: run clean
