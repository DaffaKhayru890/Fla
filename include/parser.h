#pragma once

#include "./lexer.h"
#include "./ast.h"

typedef struct {
    Lexer *lexer;
    Token *current;
    Token *peek;
}Parser;

Parser *init_parser(Lexer *l, Token *t);

Token *current_token(Parser *p);

void eat_token(Parser *p, TokenType type, Lexer *l, Token *t);
void free_parser(Parser *p);

ASTNode *parser_program(Parser *p, Lexer *l, Token *t);
ASTNode *parser_module(Parser *p, Lexer *l, Token *t);
ASTNode *parser_function_declaration(Parser *p, Lexer *l, Token *t);
ASTNode *parser_block(Parser *p, Lexer *l, Token *t);
ASTNode *parser_function_call(Parser *p, Lexer *l, Token *t);
ASTNode *parser_argument(Parser *p, Lexer *l, Token *t);
ASTNode *parser_string_literal(Parser *p, Lexer *l, Token *t);