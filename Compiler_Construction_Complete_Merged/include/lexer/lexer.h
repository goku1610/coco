#ifndef LEXER_H
#define LEXER_H

#include "lexer/lexerDef.h"
#include <stdio.h>

#define ALPHABET_SIZE 26

typedef struct trie
{
    struct trie* children[ALPHABET_SIZE];
    TOKEN_TYPE tokenType;
} Trie;
typedef Trie* trie;

trie createTrieNode();
void insert(trie root, char* key, TOKEN_TYPE tokenType);
TOKEN_TYPE search(trie root, char* key);

FILE *getStream(FILE *fp);
tokenInfo getNextToken(twinBuffer B);
void removeComments(char *inputFile, char *outputFile);
tokenInfo nextToken(twinBuffer B, FILE *fp);
char *getTokenName(TOKEN_TYPE type);
void populate_buffer(twinBuffer B, FILE *fp);
void initializeLookupTable();
bool handle_valid_error(tokenInfo token);
void resetLexicalErrorCount(void);
int getLexicalErrorCount(void);

#endif
