#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_variable_declaration() {
    ASTNode *variable_declaration = (ASTNode*)malloc(sizeof(ASTNode));

    if(variable_declaration == NULL) {
        fprintf(stderr, "Error: failed to create variable declaration\n");
        exit(EXIT_FAILURE);
    }

    variable_declaration->type = NODE_VARIABLE_DECLARATION;
    variable_declaration->child = NULL;

    return variable_declaration;
}