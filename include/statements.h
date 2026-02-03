#ifndef FLA_STATEMENTS_H
#define FLA_STATEMENTS_H

#include "../../include/node.h"

typedef struct {
    char *identifier;
    char *return_type;
    char* function_name;
    ASTNode* arguments;    
    int arg_count;
    int arg_capacity;
}FunctionDeclaration;

typedef struct {
    ASTNode* return_value;
}Return;

typedef struct {
    ASTNode *statements;
    int count;
    int capacity;
}Block;

typedef struct {
    char *identifier;
    char *type;
}VariableDeclaration;

typedef struct {
    int elseif_count;
    ASTNode* condition;     
    ASTNode* then_branch;   
    ASTNode* else_branch;   
}If;

typedef struct {
    ASTNode* condition;   
    ASTNode* body;  
}While;

typedef struct {
    ASTNode* initializer;   
    ASTNode* condition;     
    ASTNode* increment;     
    ASTNode* body;          
}For;

typedef struct {
    
}Break;

typedef struct {
    
}Continue;

typedef struct {
    int case_count;
    ASTNode *expression;
    ASTNode *body;
}Switch;

#endif