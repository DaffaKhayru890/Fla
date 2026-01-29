#pragma once 

#include "stdbool.h"

#define MAX_LITERAL 256

typedef enum {
    TK_KEYWORD,
    TK_IDENTIFIER,
    TK_STRING,
    TK_NUMBER,
    TK_LPAREN,
    TK_RPAREN,
    TK_RARROW,
    TK_SEMICOLON,
    TK_COLON,
    TK_ASSIGN,
    TK_EMPTY,
    TK_EOF
}TokenType;

typedef struct {
    TokenType type;
    char literal[MAX_LITERAL];
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
Token *read_string(Lexer *l, Token *t);
Token *read_digit(Lexer *l, Token *t);
Token *read_rarrow(Lexer *l, Token *t);

Token *tokenize(Lexer *l, Token *t);