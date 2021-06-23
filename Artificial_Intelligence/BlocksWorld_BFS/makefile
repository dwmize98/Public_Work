all: state.o node.o BlocksworldBFS.o
	c++ -std=c++11 state.o node.o BlocksworldBFS.o -o BlocksworldBFS
state.o:
	c++ -std=c++11 -c -g state.cpp
node.o:
	c++ -std=c++11 -c -g node.cpp
BlocksworldBFS.o:
	c++ -std=c++11 -c -g BlocksworldBFS.cpp
clean: 
	rm *.o BlocksworldBFS
