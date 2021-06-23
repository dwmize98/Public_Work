#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "NatDed.h"

using namespace std;

Expr* ROI::ModusPonens(Expr* s1, Expr* s2) {
    
    if (s1->sub.at(0)->sym == "implies") {

        if (Eq(s1->sub.at(1), s2)) {
            Expr* s3 = new Expr(s1->sub.at(2));
            cout << s3->toString() << endl;
            return s3;
        } 
        else {
            throw RuleApplicationError("Invalid Modus Ponens");
        }
    }
    else {
        throw RuleApplicationError("Invalid Modus Ponens");
    }

}

Expr* ROI::ImplicationElimination(Expr* s1) {
   
    if (s1->sub.at(0)->sym == "implies") {
        vector<Expr*> L; //The entire new statement
        vector<Expr*> L2; //Adds the not to the left side of the implication
        L2.push_back(parse("not "));
        L2.push_back(s1->sub.at(1));
        Expr* not_a = new Expr(L2);
        
        L.push_back(parse("or"));
        L.push_back(not_a);
        L.push_back(s1->sub.at(2));
        Expr* s3 = new Expr(L);

        cout << s3->toString() << endl;
        return s3;

    }
    else {
        throw RuleApplicationError("Invalid Implication Elimination");
    }
}

Expr* ROI::AndElimination(Expr* s1, Expr* s2) {
    
    if (s1->sub.at(0)->sym == "and") {
        int i = 1;
        while (!Eq(s1->sub.at(i), s2)) //Isolates the desired element to return
            i++;

        Expr* s3 = new Expr(s1->sub.at(i));
        cout << s3->toString() << endl;
        return s3;
    }
    
    else {
        throw RuleApplicationError("Invalid And Elimination");
    }
}

Expr* ROI::AndIntroduction(Expr* s1, Expr* s2) {

    vector<Expr*> L;
    L.push_back(parse("and"));
    L.push_back(s1);
    L.push_back(s2);
    Expr* s3 = new Expr(L);
    cout << s3->toString() << endl;
    return s3;
}

Expr* ROI::OrIntroduction(Expr* s1, Expr* s2) {

    vector<Expr*> L;
    L.push_back(parse("or"));
    L.push_back(s1);
    L.push_back(s2);
    Expr* s3 = new Expr(L);
    cout << s3->toString() << endl;
    return s3;

}

Expr* ROI::DoubleNegationElimination(Expr* s1) {
    
    if(s1->sub.at(0)->sym == "not" && s1->sub.at(1)->sub.at(0)->sym == "not") {
        Expr* s3 = new Expr(s1->sub.at(1)->sub.at(1));
        cout << s3->toString() << endl;
        return s3;
    }

    else {
        throw RuleApplicationError("Invalid Double Negation Elimination");
    }
}

Expr* ROI::Resolution(Expr* s1, Expr* s2) {
    
    if (s1->sub.at(0)->sym == "or" && s2->sub.at(0)->sym == "or") {
        vector<Expr*> L;
        L.push_back(s1->sub.at(1));
        L.push_back(s1->sub.at(2));
        L.push_back(s2->sub.at(1));
        L.push_back(s2->sub.at(2));
        //Everything is pushed to a vector.
        //The first to elements are then compared to the last two elements
        //The match that was one negated and the other not negated is then removed

        for (int i = 0; i < L.size()/2; i++) {
            for (int j = 2; j < L.size(); j++) {
                if (L.at(i)->kind == LIST && L.at(j)->kind == ATOM) {
                     if (Eq(L.at(i)->sub.at(1), L.at(j))) {
                        L.erase(L.begin() + i);
                        L.erase(L.begin() + j - 1);
                        break;
                    }
                }
                else if (L.at(i)->kind == ATOM && L.at(j)->kind == LIST) {
                     if (Eq(L.at(i), L.at(j)->sub.at(1))) {
                        L.erase(L.begin() + i);
                        L.erase(L.begin() + j - 1);
                        break;
                     }
                }
            }
        }

        if (L.size() == 4) {
            throw RuleApplicationError("Invalid Resolution");
        }

        L.insert(L.begin(), parse("or"));
        Expr* s3 = new Expr(L);
        cout << s3->toString() << endl;
        return s3;
        }

    else {
        throw RuleApplicationError("Invalid Resolution");
    }

}

Expr* ROI::DeMorgansLaw(Expr* s1) {

    if (s1->sub.at(0)->sym == "not") {
        vector<Expr*> L;
        for (int i = 0; i < s1->sub.at(1)->sub.size(); i++) {
                Expr* curr = s1->sub.at(1)->sub.at(i);
                if (curr->sym == "and") //First few line flip the sign
                    L.push_back(parse("or"));
                else if (curr->sym == "or")
                    L.push_back(parse("and"));
                else if (curr->kind == LIST && curr->sub.at(0)->sym == "not") //Looks for any negations and then flips the sign if one is found
                    L.push_back(curr->sub.at(1));
                else
                    L.push_back(parse("(not " + curr->sym + ")")); //otherwise the current value is negated
        }
        Expr* s3 = new Expr(L);
        cout << s3->toString() << endl;
        return s3;
    }

    else {
        throw RuleApplicationError("Invalid DeMorgan's Law");
    }
}
