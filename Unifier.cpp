#include "Unifier.h"
#include "Expr.h"
using namespace std;

Unifier::Unifier() {
    subList = new unordered_map<string, string>();
}

Unifier::Unifier(Unifier* u) {
    subList = new unordered_map<string, string>();
    auto iter = u->subList->begin();
    while (iter != u->subList->end()) {
        subList->insert(make_pair(iter->first, iter->second));
        iter++;
    }
}

Unifier* unify(Expr* a, Expr* b) {
    Unifier* u = new Unifier();
    return unify(a, b, u);
}

Unifier* unify(Expr* a, Expr* b, Unifier* theta) {
    if (theta == nullptr) return nullptr;
    else if (a->toString() == b->toString()) return theta;
    else if (a->isVar()) return unifyVar(a, b, theta);
    else if (b->isVar()) return unifyVar(b, a, theta);
    else if (a->isList() && b->isList()) {
        vector<Expr*> aList = a->getList();
        vector<Expr*> bList = b->getList();
        vector<Expr*> aRest, bRest;
        for (int i = 1; i < aList.size(); i++) {
            aRest.push_back(aList[i]);
        }
        for (int i = 1; i < bList.size(); i++) {
            bRest.push_back(bList[i]);
        }
        Expr *aExpr, *bExpr;
        aExpr = (aRest.size() == 1) ? aRest[0] : new Expr(aRest);
        bExpr = (bRest.size() == 1) ? bRest[0] : new Expr(bRest);
        Unifier* thetaP = unify(aList[0], bList[0], theta);
        return unify(aExpr, bExpr, thetaP);
    }
    else return nullptr;
}



Unifier* unifyVar(Expr* a, Expr*b, Unifier* theta) {
    auto valA = theta->subList->find(a->toString());
    auto valB = theta->subList->find(b->toString());
    if (valA != theta->subList->end()) {
        Expr* val = new Expr(valA->second);
        return unify(val, b, theta);
    }
    else if (valB != theta->subList->end()) {
        Expr* val = new Expr(valB->second);
        return unify(a, val, theta);
    }
    else {
        theta->getList()->insert(make_pair(a->toString(), b->toString()));
        return theta;
    }
}

void Unifier::print() {
    auto iter = subList->begin();
    while (iter != subList->end()) {
        cout << iter->first << "=" << iter->second << endl;
        iter++; 
    }
}

string Unifier::find(string key) {
    return subList->find(key)->second;
}

Sub Unifier::getList() {
    return subList;
}

Expr* subst(Expr* a, Unifier* u) {
    vector<Expr*> list = a->getList();
    vector<Expr*> expr;
    for (int i = 0; i < list.size(); i++) {
        if (list[i]->isVar() && u->subList->find(list[i]->toString()) != u->subList->end()) {
            expr.push_back(new Expr(u->find(list[i]->toString())));
        }
        else {
            expr.push_back(new Expr(list[i]->toString()));
        }
    }
    return new Expr(expr);
}

void compose(Unifier* a, Unifier* b) {
    for (auto iter = b->subList->begin(); iter != b->subList->end(); iter++) {
        string key = iter->first;
        auto elem = a->subList->find(key);
        if (elem == a->subList->end()) {
            a->subList->insert(make_pair(key, b->subList->find(key)->second));
        }
        else if (elem->second != b->subList->find(key)->second) {
            a = nullptr;;
        }
    }
}