#include "state.h"
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

void State::print() {
    for (unsigned int i = 0; i < blocks.size(); i++) {
        cout << blocks.at(i) << endl;
    }
    cout << ">>>>>>>>>>>>>>>" << endl;
}

string State::hash() {
    string unique_hash = "";
    for (int i = 0; i < blocks.size(); i++) {
        unique_hash += blocks.at(i) + ";";
    }
    return unique_hash;
}

bool State::match(State* compare) {
    if (compare->blocks.size() != blocks.size()) {
        return false;
    }
    
    else {
        for (int i = 0; i < blocks.size(); i++) {
            if (blocks.at(i) != compare->blocks.at(i)) {
                return false;
            }
        }
        return true;
    }
}

vector<State*> State::successors() {
    vector<State*> children;
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks.size(); j++) {
            if (i == j) {
                j++;
            }

            else {
                State* child_take = new State(blocks);
                if (child_take->blocks.at(j).size() > 0) {
                    child_take->blocks.at(i).push_back(child_take->blocks.at(j).back());
                    child_take->blocks.at(j).pop_back();
                    children.push_back(child_take);
                }

                State* child_give = new State(blocks);
                if (child_give->blocks.at(i).size() > 0) {
                    child_give->blocks.at(j).push_back(child_give->blocks.at(i).back());
                    child_give->blocks.at(i).pop_back();
                    children.push_back(child_give);
                }
                
            }
        }
    }
    return children;
}

float State::heuristic(State& goal) {

    int y = 0;
    int diff = 0;
    float weight = 0;
    bool placed = true; //flag used to keep track of whether or not all blocks in the column are palced correctly so far.

    for (int i = 0; i < blocks.size(); i++) {

        if (blocks.at(i).length() > goal.blocks.at(i).length()) {           //first calcuation is finding the difference in length between a column of the current
            y = goal.blocks.at(i).length();                                 //state and column of the goal state.
            diff = blocks.at(i).length() - goal.blocks.at(i).length();        
        }
        else {
            y = blocks.at(i).length();
        }
    
        for (int j = 0; j < y; j++) {                                       
            if (blocks.at(i).at(j) == goal.blocks.at(i).at(j)) {            //if a matched is found, but the blocks below are not in the right order, a weight is added.
                if (!placed) {
                    weight += 4;
                }
            }
            else {                                                          //if the blocks don't match, then a weight is added, and the flag is changed to false
                weight += 2;
                placed = false;
            }
            for (int l = 0; l < y; l++) {                                   //this for loops checks to see if there are two blocks of the same type in the same column
                if(l != j && blocks.at(i).at(j) == goal.blocks.at(i).at(l)) { //but they aren't in the correct place. It then adds a weight.
                    weight += 2;
                }
            }
        }
        
        weight += (2*diff);                                                 //the diff in column lengths is multiplied by two and added to the weight.
        placed = true;
        diff = 0;
    }

    return weight;
}
