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
