#include "node.h"
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

bool Node::goal_test(State* compare) {
    return currstate->match(compare);
}


vector<Node*> Node::successors() {
    
    vector<State*> children_states = currstate->successors();

    vector<Node*> children_nodes;

    for (int i = 0; i < children_states.size(); i++) {
        Node* child_node = new Node(this, children_states.at(i), this->depth+1);
        children_nodes.push_back(child_node);
    }

    return children_nodes;

}

string Node::hash() {
    return currstate->hash();
}


int Node::print_path() {
    
    if (this->parent) {
        this->parent->print_path();
    }

    cout << "move " << depth << endl;
    this->currstate->print();

    return 1;
}
