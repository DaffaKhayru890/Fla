#ifndef FLA_PARSER_H
#define FLA_PARSER_H

#include "./lexer.h"
#include "./ast.h"

typedef struct {
    Lexer *lexer;
    Token current;
    Token next;
}Parser;

void createParser(Parser *p, Lexer *l);

ASTNode *parse_program(Parser *p);

#endif