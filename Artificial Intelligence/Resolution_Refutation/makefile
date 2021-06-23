all: parser.o resolution.o
	c++ -std=c++11 parser.o resolution.o -o exe

parser.o:
	c++ -std=c++11 -c parser.cpp

resolution.o:
	c++ -std=c++11 -c resolution.cpp

clean:
	rm *.o exe
