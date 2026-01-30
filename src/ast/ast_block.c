#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_block_node() {
    ASTNode *block_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(block_node == NULL) {
        fprintf(stderr, "Error: failed to init block node\n");
        exit(EXIT_FAILURE);
    }

    block_node->type = NODE_BLOCK;
    block_node->children = NULL;
    block_node->child_count = 0;

    return block_node;
}