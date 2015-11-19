CC = gcc
CXXFLAGS = -L/opt/local/lib -I/opt/local/include -lprotobuf

main: main.cc main.pb.cc

main.pb.cc: main.proto
	protoc main.proto --cpp_out=.

run:
	./main
