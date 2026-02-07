#ifndef FLA_EXPRESSION_H
#define FLA_EXPRESSION_H

#include "./node.h"
#include "./literal.h"

typedef struct {
    char *op;
    ASTNode *left;
    ASTNode *right;
}Binary;

typedef struct {
    char *op;
    ASTNode *operand;
    bool is_postfix;
}Unary;

typedef struct {
    ASTNode *condition;
    ASTNode *then_expr;
    ASTNode *else_expr;
}Ternary;

typedef struct {
    ASTNode *expression;
}Grouping;

typedef struct {    
    int count;
    int capacity;
    ASTNode **body;
}Compound;

typedef struct {
    char *function_name;
    ASTNode **arguments;     
    int arg_count;
}FunctionCall;

typedef struct  {
    char *identifier;    
}Identifier;


#endif