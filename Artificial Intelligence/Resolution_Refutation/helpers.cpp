#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "parser.hpp"

using namespace std;

class ResPair {
    public:
        int i, j, score;
        ResPair(int a, int b, int s) {i=a; j=b; score=s;}
};

Expr* resolve(Expr* clause1, Expr* clause2, string prop) {
    
    if (clause1->sub.at(0)->sym == "or" && clause2->sub.at(0)->sym == "or") {
        vector<Expr*> left;
        vector<Expr*> right;

        for (int i = 1; i < clause1->sub.size(); i++) {
            string value = clause1->sub.at(i)->kind == ATOM ? clause1->sub.at(i)->toString() : clause1->sub.at(i)->sub.at(1)->toString();
            if (value != prop) {
                left.push_back(clause1->sub.at(i));
            }
        }
        for (int i = 1; i < clause2->sub.size(); i++) {
            string value = clause2->sub.at(i)->kind == ATOM ? clause2->sub.at(i)->toString() : clause2->sub.at(i)->sub.at(1)->toString();
            if (value != prop) {
                right.push_back(clause2->sub.at(i));
            }
        }

        for (int i = 0; i < left.size(); i++) { //factors out the clauses
            for (int j = 0; j < right.size(); j++) {
                if (Eq(left.at(i), right.at(j))) {
                    right.erase(right.begin() + j);
                    j--;
                }
            }
        }
        vector<Expr*> combined;
        combined.reserve(left.size() + right.size());
        combined.insert(combined.end(), left.begin(), left.end());
        combined.insert(combined.end(), right.begin(), right.end());

        combined.insert(combined.begin(), parse("or"));
        Expr* s3 = new Expr(combined);
        return s3;
        }

    else {
        throw RuleApplicationError("Invalid Resolution");
    }
}


vector<string> matching_propositions(Expr* clause1, Expr* clause2){ //cross references positive and negative literals from both clauses and returns them
    vector<string> clause1_positives(0);
    vector<string> clause1_negatives(0);
    vector<string> clause2_positives(0);
    vector<string> clause2_negatives(0);
    vector<string> matching(0);
    
    if (clause1->sub.at(0)->sym == "or" && clause2->sub.at(0)->sym == "or") {
        for (int i = 1; i < clause1->sub.size(); i++) { //positives of clause 1
            if (clause1->sub.at(i)->kind == ATOM) {
                clause1_positives.push_back(clause1->sub.at(i)->toString());
            }
            if (clause1->sub.at(i)->kind != ATOM) {
                clause1_negatives.push_back(clause1->sub.at(i)->sub.at(1)->toString());
            }
        }
        for (int i = 1; i < clause2->sub.size(); i++) { //negatives of clause 2
            if (clause2->sub.at(i)->kind == ATOM) {
                clause2_positives.push_back(clause2->sub.at(i)->toString());
            }
            if (clause2->sub.at(i)->kind != ATOM) {
                clause2_negatives.push_back(clause2->sub.at(i)->sub.at(1)->toString());
            }
        }

        for (int i = 0; i < clause1_positives.size(); i++) {
            for (int j = 0; j < clause2_negatives.size(); j++) {
                if (clause1_positives.at(i) == clause2_negatives.at(j)) {
                    matching.push_back(clause1_positives.at(i));
                }
            }
        }
        for (int i = 0; i < clause1_negatives.size(); i++) {
            for (int j = 0; j < clause2_positives.size(); j++) {
                if (clause1_negatives.at(i) == clause2_positives.at(j)) {
                    matching.push_back(clause2_positives.at(j));
                }
            }
        }

    return matching;
    }
    else {
        throw RuleApplicationError("Invalid Resolution");
    }

}

bool resolvable(Expr* clause1, Expr* clause2){
    vector<string> result = matching_propositions(clause1, clause2);
    return result.size() > 0;
}

bool validateClause(Expr* clause) { //walks through the clause, modifies negatives, compares all of them to themselves and returns
    if (clause->sub.at(0)->sym == "or") {
        for (int i = 1; i < clause->sub.size(); i++) {
            string held = clause->sub.at(i)->kind == ATOM ? clause->sub.at(i)->toString() : "~" + clause->sub.at(i)->sub.at(1)->toString(); 
            for (int j = i + 1; j < clause->sub.size(); j++) {
                string compared = clause->sub.at(j)->kind == ATOM ? clause->sub.at(j)->toString() : "~" + clause->sub.at(j)->sub.at(1)->toString();
                if ("~" + held == compared || held == "~" + compared ) {
                    return false;
                }
            }
        }        
        return true;
    } else {
        return false;
    }
}

Expr* negate_expr(Expr* clause) { //helper function to negate the users inputed clause
    vector<Expr*> negated;
    negated.push_back(parse("or"));
    if (clause->kind == LIST && clause->sub.at(0)->sym == "not") {
       negated.push_back(clause->sub.at(1)); 
    }
    else {
        negated.push_back(parse("(not " + clause->toString() + ")"));
    }
    Expr* n = new Expr(negated);
    return n;
}