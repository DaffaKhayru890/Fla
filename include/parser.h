#pragma once

#include "./lexer.h"
#include "./ast.h"

typedef struct {
    Lexer *lexer;
    Token *current;
    Token *peek;
}Parser;

Parser *init_parser(Lexer *l);

Token *current_token(Parser *p);

void eat_token(Parser *p, TokenType type, Lexer *l);
void free_parser(Parser *p);

ASTNode *parser_program(Parser *p, Lexer *l, char *name);
ASTNode *parser_module(Parser *p, Lexer *l, char *name);

ASTNode *parser_function_declaration(Parser *p, Lexer *l);
ASTNode *parser_block(Parser *p, Lexer *l);
ASTNode *parser_variable_declaration(Parser *p, Lexer *l);
ASTNode *parser_if(Parser *p, Lexer *l);
ASTNode *parser_while(Parser *p, Lexer *l);
ASTNode *parser_for(Parser *p, Lexer *l);
ASTNode *parser_switch(Parser *p, Lexer *l);

ASTNode *parser_binary(Parser *p, Lexer *l);
ASTNode *parser_function_call(Parser *p, Lexer *l);
ASTNode *parser_literal(Parser *p, Lexer *l);
ASTNode *parser_unary(Parser *p, Lexer *l);
ASTNode *parser_assignment(Parser *p, Lexer *l);
ASTNode *parser_paremeter(Parser *p, Lexer *l);