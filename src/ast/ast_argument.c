#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_argument_node() {
    ASTNode *argument_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(argument_node == NULL) {
        fprintf(stderr, "Error: failed to create argument node\n");
        exit(EXIT_FAILURE);
    }

    argument_node->type = NODE_ARGUMENT;
    argument_node->children = NULL;
    argument_node->child_count = 0;

    return argument_node;
}