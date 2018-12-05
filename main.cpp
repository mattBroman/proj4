#include <iostream>
#include <fstream>
#include "Backchain.h"
#include "Unifier.h"
#include "Expr.h"
using namespace std;

vector<Expr*>* constructKB(string filename) {
    ifstream file;
    file.open(filename);
    string line;
    vector<Expr*>* expressions = new vector<Expr*>();
    while(getline(file, line)) {
        vector<string>* toks = tokenize(line);
        if (toks->size() != 0) {
            Expr* expr = standardize(parse(toks));
            cout << expr->toString() << endl;
            expressions->push_back(expr); 
        }
    }
    file.close();
    return expressions;
}

void test_unifier() {
    Expr* a=parse(tokenize(string("(author huckleberry_finn ?b)")));
    Expr* b=parse(tokenize(string("(author ?a mark_twain)")));
    Unifier* u = unify(a,b);
    u->print();
    cout << subst(a,u)->toString() << EOL;
}

stack<Expr*> makeStack(Expr* query) {
    stack<Expr*> goals;
    vector<Expr*> list = query->getList();
    for (int i = 0; i < list.size(); i++) {
        goals.push(list[i]);
    }
    return goals;
}


int main(int argc, char* argv[]) {
    string filename = argv[1];
    string ask = argv[2];
    vector<Expr*>* expressions = constructKB(filename);
    vector<Expr*>* query = constructKB(ask);
    stack<Expr*> goals = makeStack(query->at(0));
    vector<Expr*> queryList = query->at(0)->getList();
    vector<Unifier*>* answers = folBcAsk(expressions, goals, new Unifier());
    for(int i = 0; i < answers->size(); i++) {
        cout <<"(";
        for (int j = 0; j < queryList.size(); j++) {
            cout << subst(queryList[j], answers->at(i))->toString();
        }
        cout << ")" << endl;
    }
    return 0; 
}

