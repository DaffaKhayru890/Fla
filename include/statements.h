#ifndef FLA_STATEMENTS_H
#define FLA_STATEMENTS_H

#include "./node.h"
#include "./literal.h"
#include <stdbool.h>

typedef struct {
    char *identifier;
    char *return_type;
    int param_count;
    ASTNode **parameters;  
    ASTNode *body;  
}FunctionDeclaration;

typedef struct {
    ASTNode *expression;
}Return;

typedef struct {
    ASTNode **statements;
    int statements_count;
}Block;

typedef struct {
    char *identifier;
    char *type;
    ASTNode *init;
    bool is_const;
}VariableDeclaration;

typedef struct {
    ASTNode *condition;     
    ASTNode *than_branch;   
    ASTNode *else_branch;   
}If;

typedef struct {
    ASTNode *condition;   
    ASTNode **body;  
}While;

typedef struct {
    ASTNode *preclause;   
    ASTNode *condition;     
    ASTNode *postclause;     
    ASTNode **body;          
}For;

typedef struct {

}Break;

typedef struct {

}Continue;

typedef struct {
    int case_count;
    ASTNode *expression;
    ASTNode **body;
}Switch;

#endif