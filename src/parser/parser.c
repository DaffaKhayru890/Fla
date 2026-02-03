#include "../../include/parser.h"
#include <stdbool.h>
#include <stddef.h>

// =============================== Helper Function ===============================

static void advanced(Parser *p) {
    p->current = p->next;

    for(;;) {
        p->next = getNextToken(p->lexer);
    }
}

static bool check(Parser *p, TokenType type) {
    return p->current.type == type;
}

static bool match(Parser *p, TokenType type) {
    if(!check(p,type)) return false;

    advanced(p);
    return true;
}

static void eatToken(Parser *p, TokenType type) {
    if(match(p, type)) {
        advanced(p);
        return;
    }
}

// ================================ Main parser ================================ 

void createParser(Parser *p, Lexer *l) {
    p->current = getNextToken(l);
    p->next = getNextToken(l);
}

ASTNode *parse_program(Parser *p) {
    ASTNode *program = NULL;

    createProgramNode(program);

    

    return program;
}