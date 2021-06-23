#include <vector>
#include <string>
#include <stdexcept>
#include "parser.hpp"

#ifndef NATDED_H
#define NATDED_H

using namespace std;

class ROI {

  public:
    static Expr* ModusPonens(Expr* s1, Expr* s2);
    static Expr* ImplicationElimination(Expr* s1);
    static Expr* AndElimination(Expr* s1, Expr* s2); //The second argument exists to specify which element to isolate from the elimination. 
    static Expr* AndIntroduction(Expr* s1, Expr* s2);
    static Expr* OrIntroduction(Expr* s1, Expr* s2);
    static Expr* DoubleNegationElimination(Expr* s1);
    static Expr* Resolution(Expr* s1, Expr* s2);
    static Expr* DeMorgansLaw(Expr* s1);
  
};



#endif
