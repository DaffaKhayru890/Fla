#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_function_call_node(char *identifier) {
    ASTNode *function_call_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(function_call_node == NULL) {
        fprintf(stderr, "Error: failed to init function call node\n");
        exit(EXIT_FAILURE);
    }

    function_call_node->type = NODE_FUNCTION_CALL;
    function_call_node->children = NULL;
    function_call_node->child_count = 0;
    function_call_node->function_call_node.identifier = strdup(identifier);

    return function_call_node;
}