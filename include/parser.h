#pragma once

#include "stdbool.h"

#include "./lexer.h"
#include "./ast.h"

typedef struct {
    Lexer *lexer;
    Token *current;
}Parser;

Parser *init_parser(Lexer *l, Token *t);

void eat_token(Parser *p, TokenType type, Lexer *l, Token *t);
void free_parser(Parser *p);

bool check_token(Parser *p, TokenType type);

Token *current_token(Parser *p);

ASTNode *parser_module(ASTNode *root_node, Parser *p, Lexer *l, Token *t);
ASTNode *parser_function_declaration(ASTNode *module_node, Parser *p, Lexer *l, Token *t);