#include "parser.h"
#include "grammar_sets.h"
#include "parse_runtime.h"

#include <stdio.h>

void printParseTree(parseTree *PT, char *outfile)
{
    if (PT == NULL || outfile == NULL)
   {
        return;
    }

    FILE *fp = fopen(outfile, "w");
   if (fp == NULL)
     {
       printf("Unable to open output file: %s\n", outfile);
        return;
    }

    printParseTreeInorder(PT, fp);

    fclose(fp);
}

void createParseTableStrict(FirstAndFollow ff, table *T)

 {
    createParseTable(ff, T);

}

FirstAndFollow ComputeFirstAndFollowSets(grammar G)
{
    return computeFirstFollowSet(G);
}

parseTree *parseInputSourceCode(char *infile, table T)
{
    if (infile == NULL)
    {
        return NULL;
    }

     FILE *fp = fopen(infile, "r");
   if (fp == NULL)
    {
        printf("Unable to open input file: %s\n", infile);
        return NULL;
    }

    grammar G = initializeGrammar();
   FirstAndFollow ff = ComputeFirstAndFollowSets(G);
    buildParseTable(ff, &T);
     parseTree *PT = parseInputSourceCodeStream(T, ff, G, fp);
     fclose(fp);
    return PT;

}

void createParseTable(FirstAndFollow ff, table *T)
{
    if (T == NULL)
    {
       return;
    }

    buildParseTable(ff, T);
}
