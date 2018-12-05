#pragma once
#include <utility>
#include "Expr.h"
#define Sub unordered_map<string,string>*

class Unifier {    

    public:
        Sub getList();
        Unifier(Unifier* u);
        Unifier();
        void print();
        Sub subList;
        string find(string key);
};


Expr* subst(Expr* a, Unifier* u);
Unifier* unify(Expr* a, Expr* b, Unifier* theta);
Unifier* unify(Expr* a, Expr*b);
Unifier* unifyVar(Expr* var, Expr* x, Unifier* theta);
void compose(Unifier* a, Unifier* b);