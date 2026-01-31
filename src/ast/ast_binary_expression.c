#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_binary_expression_node() {
    ASTNode *binary_expression = (ASTNode*)malloc(sizeof(ASTNode));

    if(binary_expression == NULL) {
        fprintf(stderr, "Error: failed to create binary expression\n");
        exit(EXIT_FAILURE);
    }

    binary_expression->type = NODE_BINARY_EXPRESSION;
    binary_expression->children = NULL;
    binary_expression->child_count = 0;

    return binary_expression;
}