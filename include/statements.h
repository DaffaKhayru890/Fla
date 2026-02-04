#ifndef FLA_STATEMENTS_H
#define FLA_STATEMENTS_H

#include "./node.h"
#include "./literal.h"

typedef struct {
    char *identifier;
    char *return_type;
    int param_count;
    ASTNode **parameters;    
}FunctionDeclaration;

typedef struct {
    ASTNode *return_value;
}Return;

typedef struct {
    ASTNode **statements;
    int count;
    int capacity;
}Block;

typedef struct {
    char *identifier;
    char *type;
    ASTNode *init;
}VariableDeclaration;

typedef struct {
    int elseif_count;
    ASTNode *condition;     
    ASTNode **then_branch;   
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