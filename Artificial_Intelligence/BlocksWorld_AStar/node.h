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
        float cost;
        State* goal;
        
        
        //Node(Node* p, State* c, int d) : parent(p), currstate(c), depth(d) {}; 
        Node() : parent(nullptr), currstate(nullptr), depth(0) {};
        Node(Node* p, State* c, int d, State* goal);
        bool goal_test(State*);
        vector<Node*> successors();
        string hash();
        int print_path();

};

struct CompareWeight {
    bool operator()(Node const *n1, Node const *n2) {
        return n1->cost > n2->cost;
    }

};




#endif
