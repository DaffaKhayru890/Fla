#pragma once 

#include "stdbool.h"

typedef enum {
    TK_KEYWORD,
    TK_IDENTIFIER,
    TK_NUMBER,
    TK_LPAREN,
    TK_RPAREN,
    TK_LBRACE,
    TK_RBRACE,
    TK_SEMICOLON,
    TK_EMPTY,
    TK_EOF
}TokenType;

typedef struct {
    TokenType type;
    char literal[256];
}Token;

typedef struct {
    char *input;
    char ch;
    int pos;
    int line;
    int column;
}Lexer;

Lexer *init_lexer(char *input);
Token *init_token(void);

void advanced(Lexer *l);
void skip_whitespace(Lexer *l);
bool is_keyword(Lexer *l, char *keyword);
void create_token(Lexer *l, Token *t, TokenType type, char *literal_char);
void free_lexer(Lexer *l, Token *t);

Token *read_keyword(Lexer *l, Token *t);
Token *read_digit(Lexer *l, Token *t);

Token *tokenize(Lexer *l, Token *t);