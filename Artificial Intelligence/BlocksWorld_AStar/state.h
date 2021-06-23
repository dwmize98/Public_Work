#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class State {
    
    private:

        vector<string> blocks;


    public:

        State(vector<string> b) : blocks(b) {};
        void print();
        bool match(State*);
        string hash();
        vector<State*> successors();
        float heuristic(State& goal);
};




#endif
