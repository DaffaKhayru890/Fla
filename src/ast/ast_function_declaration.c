#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode* create_function_declaration_node(char *identifier, char *return_type) {
    ASTNode *function_declaration_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(function_declaration_node == NULL) {
        fprintf(stderr, "Error: failed to init function declaration\n");
        exit(EXIT_FAILURE);
    }

    function_declaration_node->type = NODE_FUNCTION_DECLARATION;
    function_declaration_node->function_declaration.identifier = strdup(identifier);
    function_declaration_node->function_declaration.return_type = strdup(return_type);
    function_declaration_node->children = NULL;
    function_declaration_node->child_count = 0;

    return function_declaration_node;
}