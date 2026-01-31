#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

Parser *init_parser(Lexer *l) {
    Parser *parser = (Parser*)malloc(sizeof(Parser));

    if(parser == NULL) {
        fprintf(stderr, "Error: failed to init parser\n");
        exit(EXIT_FAILURE);
    }

    parser->lexer = l;
    parser->current = tokenize(l);

    return parser;
}

void free_parser(Parser *p) {
    if(p != NULL) {
        if(p->current != NULL) {
            free(p->current);
        }
        
        free(p);
    }

    return;
} 

char *token_names[] = {
    "TK_KEYWORD_MODULE",
    "TK_KEYWORD_FUN",
    "TK_KEYWORD_VOID",
    "TK_KEYWORD_DO",
    "TK_KEYWORD_END",
    "TK_IDENTIFIER",
    "TK_STRING",
    "TK_NUMBER",
    "TK_LPAREN",
    "TK_RPAREN",
    "TK_RARROW",
    "TK_SEMICOLON",
    "TK_COLON",
    "TK_ASSIGN",
    "TK_EMPTY",
    "TK_EOF"
};

void eat_token(Parser *p, TokenType type, Lexer *l) {
    if(p->current->type == type) {
        free(p->current);
        p->current = tokenize(l);
    }else {
        fprintf(stderr, "Error: parse failed, expected type %s, but get %s\n", token_names[type], token_names[p->current->type]);
        exit(EXIT_FAILURE);
    }
}