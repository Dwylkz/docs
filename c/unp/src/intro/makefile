CC = gcc
CFLAGS = -I../unpv13e/lib -Idlib/src -g -O2 -D_REENTRANT 
LIBS = ../unpv13e/libunp.a -lpthread dlib/src/libdlib.a

PID=4898
HOST = 127.0.0.1
PORT = 60008
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
	@#./main tcpserv01
	@#./main echosrv $(PORT)
	@./main plussrv $(PORT)

cli:
	@#./main tcpcli01 $(HOST) $(PORT) 0
	@#./main replcli $(HOST) $(PORT)
	@./main replcli2 $(HOST) $(PORT)

test:
	@#./main multireq 10 $(HOST)
	@echo "test" | ./main tcpcli01test 10 $(HOST) $(PORT) 1

l:
	@ps -ott,pid,ppid,stat,nwchan,command

n:
	@netstat -finet -ptcp | grep $(PORT)

t:
	@telnet $(HOST) $(PORT)

clean:
	rm -f $(PROGS)

k:
	@kill -9 $(PID)

%: %.c
	gcc $(CFLAGS) $< $(LIBS) -o $@

.PHONY: run clean
