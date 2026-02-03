#ifndef FLA_STATEMENTS_H
#define FLA_STATEMENTS_H

#include "./node.h"
#include "./literal.h"

typedef struct {
    NodeType node_type;
    char *identifier;
    char *return_type;
    ASTNode *arguments;    
    int arg_count;
    int arg_capacity;
}FunctionDeclaration;

typedef struct {
    NodeType node_type;
    ASTNode *return_value;
}Return;

typedef struct {
    NodeType node_type;
    ASTNode *statements;
    int count;
    int capacity;
}Block;

typedef struct {
    char *identifier;
    char *type;
    ASTNode *init;
}VariableDeclaration;

typedef struct {
    NodeType node_type;
    int elseif_count;
    ASTNode *condition;     
    ASTNode *then_branch;   
    ASTNode *else_branch;   
}If;

typedef struct {
    NodeType node_type;
    ASTNode *condition;   
    ASTNode *body;  
}While;

typedef struct {
    NodeType node_type;
    ASTNode *preclause;   
    ASTNode *condition;     
    ASTNode *postclause;     
    ASTNode *body;          
}For;

typedef struct {
    NodeType node_type;
}Break;

typedef struct {
    NodeType node_type;
}Continue;

typedef struct {
    NodeType node_type;
    int case_count;
    ASTNode *expression;
    ASTNode *body;
}Switch;

#endif