#include "../../include/parser.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

// =============================== Helper Function ===============================

void advanced(Parser *p, Lexer *l) {
    p->current = p->next;
    p->next = getNextToken(l);
}

bool match(Parser *p, TokenType type) {
    if(!check(p,type)) return false;

    return true;
}

void eatToken(Parser *p, Lexer *l, TokenType type) {
    if(!match(p, type)) {
        fprintf(stderr, "Error: token does not match");
        exit(EXIT_FAILURE);
    }

    advanced(p, l);
}

// ================================ Main parser ================================ 

void createParser(Parser *p, Lexer *l) {
    p->current = getNextToken(l);
    p->next = getNextToken(l);
}

ASTNode *parseProgram(Parser *p, Lexer *l) {
    ASTNode *programNode = NULL;

    createProgramNode(&programNode);

    return programNode;
}

ASTNode *parseModule(Parser *p, Lexer *l) {
    ASTNode *moduleNode = NULL;

    createModuleNode(&moduleNode, "main");

    switch(p->current.type) {
        case TOK_KEY_FUN:
            ASTNode *parse_func_decl = parseFuncDecl(p, l);
            moduleNode->body = parse_func_decl;
        break;
    }

    return moduleNode;
}