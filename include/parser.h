#pragma once

#include "./lexer.h"
#include "./ast.h"

typedef struct {
    Lexer *lexer;
    Token *current;
}Parser;

Parser *init_parser(Lexer *l);

Token *current_token(Parser *p);

void eat_token(Parser *p, TokenType type, Lexer *l);
void free_parser(Parser *p);

ASTNode *parser_program(Parser *p, Lexer *l);
ASTNode *parser_module(Parser *p, Lexer *l);
ASTNode *parser_function_declaration(Parser *p, Lexer *l);
ASTNode *parser_block(Parser *p, Lexer *l);
ASTNode *parser_function_call(Parser *p, Lexer *l);
ASTNode *parser_argument(Parser *p, Lexer *l);
ASTNode *parser_string_literal(Parser *p, Lexer *l);