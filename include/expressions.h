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
    char *identifier;
}Identifier;

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
    char *function_name;
    ASTNode **arguments;     
    int arg_count;
}FunctionCall;

typedef struct {
    int literal_count;
    ASTNode **literal;
}Array;

typedef struct {
    ASTNode *expression;
    char *left;
    char *identifier;
}Assignment;

#endif