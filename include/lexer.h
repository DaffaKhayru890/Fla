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
    TK_KEYWORD_INT,
    TK_KEYWORD_DOUBLE,
    TK_KEYWORD_CHAR,
    TK_KEYWORD_BOOLEAN,
    TK_KEYWORD_STRING,
    TK_KEYWORD_TRUE,
    TK_KEYWORD_FALSE,
    TK_PLUS,
    TK_MINUS,
    TK_MULTIPLY,
    TK_DIVISION,
    TK_MODULO,
    TK_EQUAL,
    TK_COMMA,
    TK_NOT_EQUAL,
    TK_GREATER_THAN,
    TK_GREATER_THAN_EQUAL,
    TK_LESS_THAN,
    TK_LESS_THAN_EQUAL,
    TK_OR,
    TK_AND,
    TK_ASSIGN_EQUAL,     
    TK_ASSIGN_PLUS,       
    TK_ASSIGN_MINUS,        
    TK_ASSIGN_MULTIPLY,        
    TK_ASSIGN_DIVISION,        
    TK_ASSIGN_MODULO,
    TK_INCREMENT,     
    TK_DECREMENT,        
    TK_BITWISE_AND,
    TK_BITWISE_OR, 
    TK_BITWISE_XOR,
    TK_TERNARY_OPERATOR,
    TK_EXPONENT,
    TK_IDENTIFIER,
    TK_STRING,
    TK_NUMBER,
    TK_CHAR,
    TK_DOUBLE,
    TK_LPAREN,
    TK_RPAREN,
    TK_LSQUARE,
    TK_RSQUARE,
    TK_RARROW,
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
Token *read_char(Lexer *l, Token *t);
Token *read_digit(Lexer *l, Token *t);
Token *read_two_char_token(Lexer *l, Token *t, TokenType token_type, char first, char second);

Token *tokenize(Lexer *l);