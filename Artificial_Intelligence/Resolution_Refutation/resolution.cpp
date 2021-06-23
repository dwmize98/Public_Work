#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include "parser.hpp"
#include "helpers.cpp"


using namespace std;

//overload operator for priority queue
bool operator<(const ResPair& a, const ResPair& b) {
    return a.score > b.score;
}

bool resolution(vector<Expr*> kb, Expr* q) {
    
    Expr * negated_q = negate_expr(q);
    kb.push_back(negated_q);

    for (int i = 0; i < kb.size(); i++) {
        if (validateClause(kb.at(i)) == false) {
            return false;
        }
    }
    priority_queue<ResPair> clauses;
    for (int i = 0; i < kb.size(); i++) {
        for (int j = i + 1; j < kb.size(); j++) {
            if (resolvable(kb.at(i), kb.at(j))) {
                //unit-clause heuristic
                int score = kb.at(i)->sub.size() == 2 || kb.at(j)->sub.size() == 2 ? 1 : kb.at(i)->sub.size() + kb.at(j)->sub.size(); 

                ResPair pair(i, j, score);
                clauses.push(pair);
            }
        }
    }
    int iter = -1;
    while (!clauses.empty() && iter < 10000) {
        iter++;
        cout << "iteration=" << iter << ", " << "clauses=" << clauses.size() << endl;
        ResPair curr = clauses.top();
        clauses.pop();
        vector<string> props = matching_propositions(kb.at(curr.i), kb.at(curr.j));
        cout << "resolving clauses " << curr.i << " and " << curr.j << ": " << kb.at(curr.i)->toString() << ", " << kb.at(curr.j)->toString() << endl;
        for (int i = 0; i < props.size(); i++) {
            Expr * resolvent = resolve(kb.at(curr.i), kb.at(curr.j), props.at(i));
            cout << "resolvent = " << resolvent->toString() << endl;
            if (resolvent->sub.size() == 1) {
                return true;
            }
            if (!validateClause(resolvent)) {
                cout << endl << endl;
                continue;
            }
            bool keep_going = true;
            for (int j = 0; j < kb.size(); j++) {
                if (Eq(resolvent, kb.at(j))) {
                    keep_going = false;
                }
            }
            if (!keep_going) {
                cout << endl << endl;
                continue;
            }
            for (int j = 0; j < kb.size(); j++) {
                if (resolvable(resolvent, kb.at(j))) {
                    int updated_score = resolvent->sub.size() == 2 or kb.at(j)->sub.size() == 2 ? 1 : resolvent->sub.size() + kb.at(j)->sub.size();
                    ResPair pair(kb.size(), j, updated_score);
                    clauses.push(pair);
                }
            }
            kb.push_back(resolvent);
            cout << kb.size() - 1 << ". " << kb.back()->toString() << endl << endl;
        }
    }
    return false;
}



int main(int argc, char **argv) {
    try {
        Expr* q = parse((string)(argv[argc - 1]));
        string filename = (string)(argv[argc - 2]);
        vector<Expr *> KB = load_kb(filename);
        if (resolution(KB, q)) {
            cout << "Success! Derived empty clause, so " << q->toString() << " is entailed" << endl;
        }
        else {
            cout << "Sorry, no solution could be found" << endl;
        }
    } catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
