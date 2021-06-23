#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "NatDed.h"
#include "parser.hpp"

using namespace std;

int main(int argc, char **argv) {
    try {    
        if ((string)(argv[argc - 1]) == "test") { //This tests all the implemented ROIs and outputs them
            Expr* s1 = parse("(implies P Q)");
            Expr* s2 = parse("P");
            Expr* s3 = parse("(and P Q)");
            Expr* s4 = parse("Q");
            Expr* s5 = parse("(not (not P))");
            Expr* s6 = parse("(or P Q)");
            Expr* s7 = parse("(or (not P) R)");
            Expr* s8 = parse("(not (or P Q))");
            cout << "Modus Ponens(P->Q, P)" << endl;
            ROI::ModusPonens(s1, s2);
            cout <<  "--------------------" << endl;
            cout << "Implication Elimination(P->Q)" << endl;
            ROI::ImplicationElimination(s1);
            cout <<  "--------------------" << endl;
            cout << "And Elimination(P ^ Q)" << endl;
            ROI::AndElimination(s3, s2);
            cout <<  "--------------------" << endl;
            cout << "And Introdution(P, Q)" << endl;
            ROI::AndIntroduction(s2, s4);
            cout <<  "--------------------" << endl;
            cout << "Or Introdution(P, Q)" << endl;
            ROI::OrIntroduction(s2, s4);
            cout <<  "--------------------" << endl;
            cout << "Double Negation Elimination(~~P)" << endl;
            ROI::DoubleNegationElimination(s5);
            cout <<  "--------------------" << endl;
            cout << "Resolution(P v Q, ~P v R)" << endl;
            ROI::Resolution(s6, s7);
            cout <<  "--------------------" << endl;
            cout << "DeMorgan's Law(~(P v Q))" << endl;
            ROI::DeMorgansLaw(s8);
            cout <<  "--------------------" << endl;


        }



        else { //This will perform the actual natural deduction for C2W.

            vector<Expr*> KB = load_kb("sammys.kb");
            int i = 0;
            for (; i < KB.size(); i++) {
                cout << i << ". " << KB[i]->toString() << endl;
            }

            cout << ++i << ". "; 
            KB.push_back(ROI::ModusPonens(KB[8], KB[47]));
            cout << ++i << ". "; 
            KB.push_back(ROI::AndIntroduction(KB[46], KB[48]));
            cout << ++i << ". "; 
            KB.push_back(ROI::ModusPonens(KB[41], KB[49]));
            cout << ++i << ". "; 
            KB.push_back(ROI::ModusPonens(KB[16], KB[50]));
            cout << ++i << ". "; 
            KB.push_back(ROI::AndElimination(KB[51], parse("(not C1Y)")));
            cout << ++i << ". "; 
            KB.push_back(ROI::AndIntroduction(KB[52], KB[42]));
            cout << ++i << ". "; 
            KB.push_back(ROI::ModusPonens(KB[24], KB[53]));
            cout << ++i << ". "; 
            KB.push_back(ROI::ModusPonens(KB[9], KB[54]));
            cout << ++i << ". "; 
            KB.push_back(ROI::AndElimination(KB[55], parse("(not C2B)")));
            cout << ++i << ". "; 
            KB.push_back(ROI::AndIntroduction(KB[56], KB[44]));
            cout << ++i << ". "; 
            KB.push_back(ROI::ModusPonens(KB[20], KB[57]));
             

        }

    } catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
