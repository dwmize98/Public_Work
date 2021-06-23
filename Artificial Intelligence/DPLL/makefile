all: parser.o DPLL.o
	c++ -std=c++11 parser.o DPLL.o -o DPLL

parser.o:
	c++ -std=c++11 -c parser.cpp

DPLL.o:
	c++ -std=c++11 -c DPLL.cpp

clean:
	rm *.o DPLL
