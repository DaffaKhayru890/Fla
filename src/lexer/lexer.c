#include "ctype.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "../../include/lexer.h"

#define MAX_LITERAL 256

Lexer *init_lexer(char *input) {
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));

    if(lexer == NULL) {
        fprintf(stderr, "Error: can not init lexer\n");
        exit(EXIT_FAILURE);
    };

    lexer->input = strdup(input);
    lexer->line = 1;
    lexer->column = 1;
    lexer->pos = 0;
    lexer->ch = lexer->input[lexer->pos];

    return lexer;
}

Token *init_token(void) {
    Token *token = (Token *)malloc(sizeof(Token));

    if(token == NULL) {
        fprintf(stderr, "Error: can not init token\n");
        exit(EXIT_FAILURE);
    };

    token->literal[0] = '\0';
    token->type = TK_EMPTY;

    return token;
}

void advanced(Lexer *l) {
    if(l->ch != '\0') {
        l->pos++;
        l->column++;
        l->ch = l->input[l->pos];
    }
}

void skip_whitespace(Lexer *l) {
    while(l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        if(l->ch == '\n') {
            l->line++;
            l->column = 0;
        }

        advanced(l);
    }
}

void create_token(Lexer *l, Token *t, TokenType type, char *literal_char) {
    strcpy(t->literal, literal_char);
    t->type = type;

    advanced(l);
}

void free_lexer(Lexer *l) {
    if(l != NULL) {
        free(l->input);
        free(l);
    }
}

void free_token(Token *t) {
    if(t != NULL) {
        free(t);
    }
}

Token *read_keyword(Lexer *l, Token *t) {
    int pos = 0;
    
    while((isalnum(l->ch) || l->ch == '_') && (pos < MAX_LITERAL-1)) {
        t->literal[pos] = l->ch;
        advanced(l);

        pos++;
    }

    t->literal[pos] = '\0';

    if(strcmp(t->literal, "fun") == 0) {
        t->type = TK_KEYWORD_FUN;

        return t;
    }else if(strcmp(t->literal, "void") == 0) {
        t->type = TK_KEYWORD_VOID;

        return t;
    }else if(strcmp(t->literal, "do") == 0) {
        t->type = TK_KEYWORD_DO;

        return t;
    }else if(strcmp(t->literal, "end") == 0) {
        t->type = TK_KEYWORD_END;

        return t;
    }else {
        t->type = TK_IDENTIFIER;

        return t;
    }
}

Token *read_string(Lexer *l, Token *t) {
    if(l->ch != '"') return NULL;
    
    int pos = 0;

    advanced(l);

    while(l->ch != '"' && l->ch != '\0' && (pos < MAX_LITERAL-1)) {
        t->literal[pos] = l->ch;
        advanced(l);

        pos++;
    }

    if(l->ch == '"') advanced(l);

    t->literal[pos] = '\0';
    t->type = TK_STRING;

    return t;
}

Token *read_digit(Lexer *l, Token *t) {
    int pos = 0;
    
    while(isdigit(l->ch) && (pos < MAX_LITERAL-1)) {
        t->literal[pos] = l->ch;
        advanced(l);

        pos++;
    }

    t->literal[pos] = '\0';

    t->type = TK_NUMBER;

    return t;
}

Token *read_rarrow(Lexer *l, Token *t) {
    if(l->ch == '-' && l->input[l->pos+1] == '>') {
        t->literal[0] = '-';
        t->literal[1] = '>';
        t->literal[2] = '\0';

        t->type = TK_RARROW;

        advanced(l);
        advanced(l);

        return t;
    }

    return t;
}

Token *tokenize(Lexer *l, Token *t) {
    TokenType token_type;

    skip_whitespace(l);

    if(l->ch == '-' && l->input[l->pos+1] == '>' && l->input[l->pos+1] != '\0') return read_rarrow(l, t);

    if(isalpha(l->ch)) {
        return read_keyword(l, t);
    }

    if(l->ch == '"') {
        return read_string(l, t);
    }

    if(isdigit(l->ch)) {
        return read_digit(l, t);
    }

    switch(l->ch) {
        case '(':
            create_token(l , t, TK_LPAREN, "(");

            return t;
        break;

        case ')':
            create_token(l , t, TK_RPAREN, ")");

            return t;
        break;

        case ':':
            create_token(l , t, TK_COLON, ":");

            return t;
        break;

        case '=':
            create_token(l , t, TK_ASSIGN, "=");

            return t;
        break;

        case '\0':
            create_token(l , t, TK_EOF, "\0");

            return t;
        break;
    }

    return t;
}