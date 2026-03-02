
#ifndef PARSE_RUNTIME_H
#define PARSE_RUNTIME_H
#include "grammar_model.h"
#include <stdio.h>

void buildParseTable(FirstFollow F, table *T);

parseTree *parseInputSourceCodeStream(table T, FirstFollow F, grammar G,
                                      FILE *fp);

void printParseTreeInorder(parseTree *PT, FILE *outfile);
void writeParseTreeDot(parseTree *PT, FILE *outfile);

FirstFollow computeFirstFollowSet(grammar G);
#endif
