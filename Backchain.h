#pragma once
#include <stack>
#include "Unifier.h"
#include "Expr.h"

vector<Unifier*>* folBcAsk(std::vector<Expr*>* kb, std::stack<Expr*> query, Unifier* theta);
std::vector<Unifier*> folBcOr(std::vector<Expr*>& kb, Expr* goal, Unifier* theta);
std::vector<Unifier*> folBcAnd(std::vector<Expr*>& kb, Expr* goals, Unifier* theta);
std::vector<Expr*> fetchRulesForGoal(std::vector<Expr*>& kb, Expr* goal);
