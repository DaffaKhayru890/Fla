#ifndef FLA_EXPRESSION_H
#define FLA_EXPRESSION_H

#include "./node.h"
#include "./literal.h"

typedef struct {
    NodeType node_type;
    char *name;
}Identifier;

typedef struct {
    NodeType node_type;
    char *op;
    ASTNode *left;
    ASTNode *right;
}Binary;

typedef struct {
    NodeType node_type;
    char *op;
    ASTNode *operand;
}Unary;

typedef struct {
    NodeType node_type;
    ASTNode *condition;
    ASTNode *then_expr;
    ASTNode *else_expr;
}Ternary;

typedef struct {
    NodeType node_type;
    ASTNode *expression;
}Grouping;

typedef struct {   
    NodeType node_type; 
    int count;
    int capacity;
}Compound;

typedef struct {
    NodeType node_type;
    char* function_name;
    ASTNode* arguments;     
    int arg_count;
    int arg_capacity;
}FunctionCall;

#endif