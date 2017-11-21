CC = g++
CXXFLAGS = -std=c++14 -Wall -O2 -g

main.exe	: main.o Graph.o
	g++ -o $@ $^
Graph.o		: Graph.cpp Graph.hpp

#----------------------------------------#

run: main.exe
	./main.exe

clean:
	rm -f *.o
	rm -f *.exe

build:
	clean main.exe

%.o: %.cpp
	g++ -std=c++14 -c $<


#========================================#
