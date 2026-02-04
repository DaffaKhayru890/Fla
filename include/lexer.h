#ifndef FLA_LEXER_H
#define FLA_LEXER_H

#include "./types.h"

#include <stdbool.h>

#define MAX_LITERAL 256
#define MESSAGE_SIZE 400

typedef struct {
    TokenType type;
    char lexeme[MAX_LITERAL];
    char message[MESSAGE_SIZE];
    bool isError;
}Token;

typedef struct {
    const char *input;
    char current;
    int pos;      
    int line;  
    int col;
}Lexer;

void createLexer(Lexer *l, const char *input);

Token getNextToken(Lexer *l);

#endif