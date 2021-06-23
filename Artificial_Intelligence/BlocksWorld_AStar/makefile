all: state.o node.o BlocksworldAstar.o
	c++ -std=c++11 state.o node.o BlocksworldAstar.o -o BlocksworldAstar
state.o:
	c++ -std=c++11 -c -g state.cpp
node.o:
	c++ -std=c++11 -c -g node.cpp
BlocksworldAstar.o:
	c++ -std=c++11 -c -g BlocksworldAstar.cpp
clean: 
	rm *.o BlocksworldAstar
