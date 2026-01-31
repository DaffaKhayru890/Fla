#pragma once 

#include "stdbool.h"

#define MAX_LITERAL 256

typedef enum {
    TK_KEYWORD_USE,
    TK_KEYWORD_FUN,
    TK_KEYWORD_DO,
    TK_KEYWORD_RETURN,
    TK_KEYWORD_END,
    TK_KEYWORD_VAR,
    TK_KEYWORD_CONST,
    TK_KEYWORD_IF,
    TK_KEYWORD_ELSE,
    TK_KEYWORD_WHILE,
    TK_KEYWORD_FOR,
    TK_KEYWORD_SWITCH,
    TK_KEYWORD_STRING,
    TK_PLUS,
    TK_MINUS,
    TK_MULTIPLY,
    TK_DIVISION,
    TK_MODULO,
    TK_EQUAL,
    TK_NOT_EQUAL,
    TK_GREATER_THAN,
    TK_GREATER_THAN_EQUAL,
    TK_LESS_THAN,
    TK_LESS_THAN_EQUAL,
    TK_OR,
    TK_AND,
    TK_EXPONENT,
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

void advanced(Lexer *l);
void skip_whitespace(Lexer *l);
void create_token(Lexer *l, Token *t, TokenType type, char *literal_char);
void free_lexer(Lexer *l);
void free_token(Token *t);

Token *read_keyword(Lexer *l, Token *t);
Token *read_string(Lexer *l, Token *t);
Token *read_digit(Lexer *l, Token *t);

Token *tokenize(Lexer *l);