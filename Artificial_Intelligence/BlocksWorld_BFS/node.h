#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <queue>
#include "state.h"

using namespace std;

class Node {
    
    public:
        Node* parent;
        State* currstate;
        int depth;
        
        Node(Node* p, State* c, int d) : parent(p), currstate(c), depth(d) {}; 
        bool goal_test(State*);
        vector<Node*> successors();
        string hash();
        int print_path();

};




#endif
