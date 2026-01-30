#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_program_node(void) {
    ASTNode *root_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(root_node == NULL) {
        fprintf(stderr, "Error: failed to initialized root node\n");
        exit(EXIT_FAILURE);
    }

    root_node->type = NODE_PROGRAM;
    root_node->children = NULL;
    root_node->child_count = 0;
    
    return root_node;
};

void add_child_to_parent_children(ASTNode *parent_node, ASTNode *child) {
    ASTNode **new_children = (ASTNode**)realloc(
        parent_node->children,
        sizeof(ASTNode*) * (parent_node->child_count + 1)
    );

    if(new_children == NULL) {
        fprintf(stderr, "Error: can not reallocate memory for new child\n");
        exit(EXIT_FAILURE);
    }

    parent_node->children = new_children;
    parent_node->children[parent_node->child_count] = child;
    parent_node->child_count += 1;
}

void free_ast_node(ASTNode *node) {
    if(node == NULL) return;

    for(int i = 0; i < node->child_count; i++) {
        free_ast_node(node->children[i]);
    }

    free(node->children);

    switch(node->type) {
        case NODE_MODULE:
            free(node->module.name);
        break;

        case NODE_FUNCTION_DECLARATION:
            free(node->function_declaration.identifier);
            free(node->function_declaration.return_type);
        break;

        case NODE_FUNCTION_CALL:
            free(node->function_call_node.identifier);
        break;

        case NODE_STRING_LITERAL:
            free(node->string_literal.value);
        break;
    
        default:
            break;
        }

    free(node);
}