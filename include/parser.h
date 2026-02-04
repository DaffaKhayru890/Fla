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

ASTNode *parseProgram(Parser *p, Lexer *l);
ASTNode *parseModule(Parser *p, Lexer *l);

ASTNode *parseFuncDecl(Parser *p, Lexer *l);
ASTNode *parseReturn(Parser *p, Lexer *l);
ASTNode *parseBlock(Parser *p, Lexer *l);
ASTNode *parseVarDecl(Parser *p, Lexer *l);
ASTNode *parseIf(Parser *p, Lexer *l);
ASTNode *parseWhile(Parser *p, Lexer *l);
ASTNode *parseFor(Parser *p, Lexer *l);
ASTNode *parseSwitch(Parser *p, Lexer *l);

void advanced(Parser *p, Lexer *l);
bool match(Parser *p, TokenType type);
void eatToken(Parser *p, Lexer *l, TokenType type);

#endif