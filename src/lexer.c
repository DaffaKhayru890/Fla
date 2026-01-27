#include "ctype.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "../include/lexer.h"

#define MAX_LITERAL 256

char *list_keywords[] = {
    "int",
    "return",
    NULL
};

Lexer *init_lexer(char *input) {
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));

    if(lexer == NULL) perror("Can not initilize lexer");

    lexer->input = input;
    lexer->line = 1;
    lexer->column = 1;
    lexer->pos = 0;
    lexer->ch = lexer->input[lexer->pos];

    return lexer;
}

Token *init_token(void) {
    Token *token = (Token *)malloc(sizeof(Token));

    if(token == NULL) perror("Can not initilize token");

    strcpy(token->literal, "");
    token->type = TK_EMPTY;

    return token;
}

void advanced(Lexer *l) {
    if(l->ch == '\0') l->ch = '\0';

    l->pos++;
    l->column++;
    l->ch = l->input[l->pos];
}

void skip_whitespace(Lexer *l) {
    while(l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        advanced(l);
    }
}

bool is_keyword(Lexer *l, char *keyword) {
    int i = 0;

    while(list_keywords[i] != NULL) {
        if(strcmp(list_keywords[i], keyword) == 0) {
            return true;
        }

        i++;
    }

    return false;
}

void create_token(Lexer *l, Token *t, TokenType type, char *literal_char) {
    strcpy(t->literal, literal_char);
    t->type = type;
}

void free_lexer(Lexer *l, Token *t) {
    if(l != NULL && t != NULL) {
        free(l);
        free(t);
    }
}

Token *read_keyword(Lexer *l, Token *t) {
    int pos = 0;
    
    while(isalnum(l->ch) && (t->literal[pos] < MAX_LITERAL-1)) {
        t->literal[pos] = l->ch;
        advanced(l);

        pos++;
    }

    t->literal[pos] = '\0';

    if(is_keyword(l, t->literal)) {
        t->type = TK_KEYWORD;

        return t;
    }else {
        t->type = TK_IDENTIFIER;

        return t;
    }
}

Token *read_digit(Lexer *l, Token *t) {
    int pos = 0;
    
    while(isdigit(l->ch) && (t->literal[pos] < MAX_LITERAL-1)) {
        t->literal[pos] = l->ch;
        advanced(l);

        pos++;
    }

    t->literal[pos] = '\0';

    t->type = TK_NUMBER;

    return t;
}

Token *tokenize(Lexer *l, Token *t) {
    TokenType token_type;

    if(l->ch == '\n') l->line++;

    skip_whitespace(l);

    if(isalpha(l->ch)) {
        return read_keyword(l, t);
    }

    if(isdigit(l->ch)) {
        return read_digit(l, t);
    }

    char ch = l->ch;

    switch(l->ch) {
        case '(':
            create_token(l , t, TK_LPAREN, "(");
            advanced(l);

            return t;
        break;

        case ')':
            create_token(l , t, TK_RPAREN, ")");
            advanced(l);

            return t;
        break;

        case '{':
            create_token(l , t, TK_LBRACE, "{");
            advanced(l);

            return t;
        break;

        case '}':
            create_token(l , t, TK_RBRACE, "}");
            advanced(l);

            return t;
        break;

        case ';':
            create_token(l , t, TK_SEMICOLON, ";");
            advanced(l);

            return t;
        break;

        case '\0':
            create_token(l , t, TK_EOF, "\0");
            
            return t;
        break;
    }

    return t;
}