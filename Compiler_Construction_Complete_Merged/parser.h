#ifndef PARSER_H
#define PARSER_H

#include "parserDef.h"

FirstAndFollow ComputeFirstAndFollowSets(grammar G);
 void printParseTree(parseTree *PT, char *outfile);
void createParseTableStrict(FirstAndFollow ff, table *T);
parseTree *parseInputSourceCode(char *infile, table T);
void createParseTable(FirstAndFollow ff, table *T);

#endif
