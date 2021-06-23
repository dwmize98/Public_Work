all: parser.o NatDed.o sammys.o
	c++ -std=c++11 parser.o NatDed.o sammys.o -o exe

parser.o:
	c++ -std=c++11 -c parser.cpp

NatDed.o:
	c++ -std=c++11 -c NatDed.cpp

sammys.o:
	c++ -std=c++11 -c sammys.cpp

clean:
	rm *.o exe
