#include "node.h"
#include <fstream>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

void bfs (vector<string> initial_blocks, vector<string> final_blocks) {
    State* initial_state = new State(initial_blocks); 
    State* final_state = new State(final_blocks);
    Node* initial_node = new Node(nullptr, initial_state, 0);


    if (initial_node->goal_test(final_state)) {
        cout << "First state and final state are the same." << endl;
        cout << "No moves required" << endl;
        return;
    }

    queue<Node*> frontier;
    frontier.push(initial_node);
    unordered_map<string, Node*> reached;
    reached[initial_node->hash()] = initial_node;
    
    Node* child_node;
    vector<Node*> children_nodes;
    int max = 0;
    int iter = 0;
    
    while(!frontier.empty() && iter < 100000) {
        if (frontier.size() > max) {
            max = frontier.size();
        }

        initial_node = frontier.front();
        frontier.pop();
        children_nodes = initial_node->successors();
        for (int i = 0; i < children_nodes.size(); i++) {
            child_node = children_nodes.at(i);
            if (child_node->goal_test(final_state)) {
                cout << "Success! iter=" << iter << ", depth=" << child_node->depth << ", max queue size=" << max << endl;
                child_node->print_path();
                return;
            }
            
            try {
                reached.at(child_node->hash());
            }
            catch (out_of_range& e){
                reached[child_node->hash()] = child_node;    
                frontier.push(child_node);
                iter++;
            }
        }

    }

    cout << "Sorry a solution could not be found" << endl;
}


int main (int argc, char** argv) {

    vector<int> meta;
    vector<string> initial_blocks;
    vector<string> final_blocks;
    bool first = true;
    string line;

    string filename = argv[1];
    ifstream f(filename);

    if (!f) {
        cout << "File could not be opened" << endl;
    } else {

        getline(f, line);

        if (first) {
            string sub = "";
            for (int i = 0; i < line.length(); i++) {
                if(line.at(i) != ' ') {
                    sub += line.at(i);   
                } else {
                    meta.push_back(stoi(sub));
                    sub = "";
                }
            }
            first = false;
        }

        getline(f, line);
        for (int i = 0; i < meta.at(0); i++) {
            getline(f, line);
            initial_blocks.push_back(line);
        }

        getline(f, line);
        for (int i = 0; i < meta.at(0); i++) {
            getline(f, line);
            final_blocks.push_back(line);
        }

    bfs(initial_blocks, final_blocks);

    }


}
