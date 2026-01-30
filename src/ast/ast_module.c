#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_module_node(char *name) {
    ASTNode *module_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(module_node == NULL) {
        fprintf(stderr, "Error: failed to init module node\n");
        exit(EXIT_FAILURE);
    }

    module_node->type = NODE_MODULE;
    module_node->module.name = strdup(name);
    module_node->children = NULL;
    module_node->child_count = 0;

    return module_node;
}

