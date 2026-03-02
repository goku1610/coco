

#ifndef PARSE_RUNTIME_H
#define PARSE_RUNTIME_H
#include "grammar_model.h"
#include <stdio.h>


 void printParseTreeInorder(parseTree *PT, FILE *fp);
 void buildParseTable(FirstFollow ff, table *T);
FirstFollow computeFirstFollowSet(grammar G);
parseTree *parseInputSourceCodeStream(table T, FirstFollow ff, grammar G,
                                      FILE *fp);

void writeParseTreeDot(parseTree *PT, FILE *fp);
#endif
