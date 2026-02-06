#ifndef FLA_STATEMENTS_H
#define FLA_STATEMENTS_H

#include "./node.h"
#include "./literal.h"
#include <stdbool.h>

typedef enum {
    VARIABLE_TYPE_VAR,
    VARIABLE_TYPE_CONST
}VarType;

typedef enum {
    RETURN_TYPE_INT,
    RETURN_TYPE_DOUBLE,
    RETURN_TYPE_FLOAT,
    RETURN_TYPE_CHAR,
    RETURN_TYPE_VOID,
}ReturnType;

typedef struct {
    char *identifier;
    ReturnType return_type;
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
    VarType variable_type;
}VariableDeclaration;

typedef struct {
    int elseif_count;
    ASTNode *condition;     
    ASTNode **elseif_branch;   
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