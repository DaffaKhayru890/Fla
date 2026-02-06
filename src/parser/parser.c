#include "../../include/parser.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "../../include/memory.h"

char *TokenTypeString[] = {
    // base keyword
    "TOK_KEY_USE",
    "TOK_KEY_FUN",
    "TOK_KEY_VAR",
    "TOK_KEY_CONST",
    "TOK_KEY_IF",
    "TOK_KEY_ELSE",
    "TOK_KEY_BREAK",
    "TOK_KEY_CONTINUE",
    "TOK_KEY_WHILE",
    "TOK_KEY_FOR",
    "TOK_KEY_SWITCH",
    "TOK_KEY_TRUE",
    "TOK_KEY_FALSE",

    // delimiters
    "TOK_LPAREN",
    "TOK_RPAREN",
    "TOK_LBRACE",
    "TOK_RBRACE",
    "TOK_LBRACKETS",
    "TOK_RBRACKETS",

    // unique
    "TOK_IDENTIFIER",

    // type keyword
    "TOK_TYPE_INT",
    "TOK_TYPE_DOUBLE",
    "TOK_TYPE_CHAR",
    "TOK_TYPE_STRING",
    "TOK_TYPE_BOOLEAN",

    // basic operators
    "TOK_PLUS",
    "TOK_MINUS",
    "TOK_MULTIPLY",
    "TOK_DIVISION",
    "TOK_MODULO",
    "TOK_EXPONENT",

    // condition
    "TOK_OP_EQ",
    "TOK_OP_NEQ",
    "TOK_OP_LT",
    "TOK_OP_LTE",
    "TOK_OP_GT",
    "TOK_OP_GTE",
    "TOK_OP_AND",
    "TOK_OP_OR",

    // single marks
    "TOK_OP_UNARY",
    "TOK_COMMA",
    "TOK_SEMICOLON",
    "TOK_COLON",
    "TOK_ASSIGNMENT",

    // two chars
    "TOK_RARROW",

    // assignment
    "TOK_ASSIGN_PLUS",
    "TOK_ASSIGN_MINUS",
    "TOK_ASSIGN_MULTIPLY",
    "TOK_ASSIGN_DIVISION",
    "TOK_ASSIGN_MODULO",
    "TOK_ASSIGN_BITWISE_AND",
    "TOK_ASSIGN_BITWISE_OR",
    "TOK_ASSIGN_BITWISE_XOR",
    "TOK_ASSIGN_LEFT_SHIFT",
    "TOK_ASSIGN_RIGHT_SHIFT",

    // decrement and increment
    "TOK_INCREMENT",
    "TOK_DECREMENT",

    // literal
    "TOK_STRING",
    "TOK_CHAR",
    "TOK_INT",
    "TOK_DOUBLE",
    "TOK_BOOLEAN",

    // others
    "TOK_ERROR",
    "TOK_UNKNOWN",
    "TOK_EOF"
};

// =============================== Helper Function ===============================

void advanced(Parser *p, Lexer *l) {
    p->current = p->next;
    p->next = getNextToken(l);
}

bool match(Parser *p, TokenType type) {
    return p->current.type == type;
}

void eatToken(Parser *p, Lexer *l, TokenType type) {
    if(!match(p, type)) {
        fprintf(stderr, "Error: token does not match expected %s, current %s\n", TokenTypeString[type], TokenTypeString[p->current.type]);
        exit(EXIT_FAILURE);
    }

    advanced(p, l);
}

bool hasReturnStatment(ASTNode *block) {
    if(!block || block->node_type != NODE_BLOCK_STATEMENT) return false;

    for(int i = 0; i < block->block_statement.statements_count; i++) {
        ASTNode *statement = block->block_statement.statements;

        if(!statement) continue;
        
        if(statement->node_type == TOK_KEY_RETURN) {
            return true;
        }
    }

    return false;
}

// ================================ Main parser ================================ 

void createParser(Parser *p, Lexer *l) {
    p->current = getNextToken(l);
    p->next = getNextToken(l);
}

ASTNode *parseProgram(Parser *p, Lexer *l) {
    ASTNode *programNode = NULL;

    createProgramNode(&programNode);

    programNode->body = (ASTNode**)malloc(sizeof(ASTNode));
 
    programNode->body[0] = parseModule(p,l);
    programNode->body[1] = NULL;

    return programNode;
}

ASTNode *parseModule(Parser *p, Lexer *l) {
    ASTNode *moduleNode = NULL;

    createModuleNode(&moduleNode, "main");

    int capacity = 4;
    int count = 0;

    moduleNode->module.body = (ASTNode**)malloc(sizeof(ASTNode));

    while(p->current.type != TOK_EOF) {
        switch(p->current.type) {
            case TOK_KEY_FUN:       
                if(count >= capacity) {
                    capacity = capacity * 2;
                    moduleNode->module.body = (ASTNode**)realloc(
                        moduleNode->module.body,
                        sizeof(ASTNode*)
                    );
                }

                moduleNode->module.body[count++] = parseFuncDecl(p, l);
            break;
        }
    }

    moduleNode->module.body[count] = NULL;

    // eatToken(p,l, TOK_EOF);

    return moduleNode;
}