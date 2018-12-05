#include "Backchain.h"
using namespace std;

vector<Expr*> fetchRulesForGoal(vector<Expr*>& kb, Expr* goal) {
    vector<Expr*> rules;
    for (int i = 0; i < kb.size(); i++) {
        vector<Expr*> list = kb[i]->getList();
        Expr* expr = list[list.size() - 1];
        vector<Expr*> syms = expr->getList();
        vector<Expr*> gSyms = goal->getList();
        bool rule = true;
        for (int j = 0; j < syms.size(); j++) {
            if ((!syms[i]->isVar() || !gSyms[i]->isVar()) && syms[i]->toString() != gSyms[i]->toString()) {
                rule = false;
            }
        }
        if (rule) {
            rules.push_back(kb[i]);
        }    
    }
    return rules;
}

vector<Unifier*>* folBcAsk(vector<Expr*>* kb, stack<Expr*>  goals, Unifier* theta) {
    if (goals.empty()) {
        vector<Unifier*>* v = new vector<Unifier*>();
        v->push_back(theta);
        return v;
    }
    vector<Unifier*>* answers = new vector<Unifier*>();
    Expr* first = goals.top();
    goals.pop();
    Expr* qPrime = subst(first, theta);
    for (int i = 0; i < kb->size(); i++) {
        Expr* rule = kb->at(i);
        vector<Expr*> list = rule->getList();
        Expr* ante = list[list.size() -1];
        Unifier* thetaP = unify(ante, qPrime);
        stack<Expr*> newGoals(goals);
        if (thetaP != nullptr) {
            for (int j = 0; j < list.size() - 1; j++) {
                newGoals.push(list[j]);
            }
            Unifier* u = new Unifier(theta);
            compose(u, thetaP);
            vector<Unifier*>* answerP = folBcAsk(kb, newGoals, u); 
            for (int j = 0; j < answerP->size(); j++) {
                answers->push_back(answerP->at(j));
            }
        }
    }
    return answers;

}

/*
vector<Unifier*> folBcOr(vector<Expr*>& kb, Expr* goal, Unifier* theta) {
    vector<Unifier*> ret;
    vector<Expr*> rules = fetchRulesForGoal(kb, goal);
    vector<Expr*> lhs;
    Expr* rhs = rules[rules.size() - 1];
    for (int i = 0; i < rules.size() - 1; i++) {
        lhs.push_back(rules[i]);
    }
    for (int i = 0; i < lhs.size(); i++) {
        Unifier* u = new Unifier(theta);
        vector<Unifier*> result = folBcAnd(kb, lhs[i], unify(rhs, goal, u));
        for (int j = 0; j < result.size(); j++) {
            if (result[j] != nullptr) {
                ret.push_back(result[j]);
            }
        } 
    }
    return ret;
}

vector<Unifier*> folBcAnd(vector<Expr*> kb, Expr* goals, Unifier* theta) {
    if theta == nullptr return nullptr;
    else if (goals->getList().size() == 0) {
        vector<Unifier*> ret;
        ret.push_back(theta);
        return ret;
    }
    else {
        vector<Expr*> list = goals.getList();
        Expr* first = list.at(0);
        vector<Expr*> restList;
        for (int i = 1; i < list.size(); i++) {
            restList.push_back(list[i]);
        }
        Expr* rest =  new Expr(restList);
        thetaP = folBcOr(kb, subst(theta, first), theta); 
        vector<Unifier*> thetaDP;
        for (int i = 0; i < thetaP.size(); i++) {
            result = folBcAnd(kb, rest, thetaP[i].getList()); // WTF
            for (int j = 0; j < result.size(); j++) {
                if (result[j] != nullptr) {
                    thetaDP.push_back(result[j]);
                }
            }
        }
        return thetaDP;

    }
}
*/