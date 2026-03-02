
#ifndef GRAMMAR_SETS_H
#define GRAMMAR_SETS_H
#include "grammar_model.h"


grammar initializeGrammar();
void followHelper(FirstFollow *ff, grammar_rule rule, NON_TERMINAL LHS,
 NON_TERMINAL **followDep, int *depCount);
void followDepAdd(NON_TERMINAL nt, NON_TERMINAL dep, NON_TERMINAL **followDep,
                  int *depCount);
void clearDependency(NON_TERMINAL nt, NON_TERMINAL **followDep, int *depCount,
                     FirstFollow *ff);
void computeFirstRec(FirstFollow *ff, NON_TERMINAL nt, grammar G, bool *fr);

 char *getNonTerminal(NON_TERMINAL nt);
 void firstUnion(FirstFollow *ff, NON_TERMINAL nt1, NON_TERMINAL nt2);
void followAdd(FirstFollow *ff, NON_TERMINAL nt, TOKEN_TYPE t);
#endif
