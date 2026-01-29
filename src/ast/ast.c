#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void add_children(ASTNode *parent_node, ASTNode *child_node) {
    ASTNode **new_children = (ASTNode**)realloc(
        parent_node->children,
        sizeof(ASTNode*) * (parent_node->child_count + 1)
    );

    if(new_children == NULL) {
        fprintf(stderr, "Error: can not reallocate memory for new child\n");
        exit(EXIT_FAILURE);
    }

    parent_node->children = new_children;
    parent_node->children[parent_node->child_count] = child_node;
    parent_node->child_count += 1;
}

ASTNode *create_root_node(void) {
    ASTNode *root_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(root_node == NULL) {
        fprintf(stderr, "Error: failed to initialized root node\n");
        exit(EXIT_FAILURE);
    }

    root_node->type = NODE_ROOT;
    root_node->children = NULL;
    root_node->child_count = 0;
    
    return root_node;
};

ASTNode *create_module_node(ASTNode *root_node, char *name) {
    ASTNode *module_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(module_node == NULL) {
        fprintf(stderr, "Error: failed to init module node\n");
        exit(EXIT_FAILURE);
    }

    module_node->type = NODE_MODULE;
    module_node->module.name = strdup(name);
    module_node->children = NULL;
    module_node->child_count = 0;

    add_children(root_node, module_node);

    return module_node;
}

ASTNode* create_function_declaration_node(ASTNode *module_node, ASTNode *class_node, char *identifier, char *return_type) {
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

    if(class_node == NULL) {
        add_children(module_node, function_declaration_node);
    }

    return function_declaration_node;
}

ASTNode *create_block_node(ASTNode *function_declaration_node) {
    ASTNode *block_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(block_node == NULL) {
        fprintf(stderr, "Error: failed to init block node\n");
        exit(EXIT_FAILURE);
    }

    block_node->type = NODE_BLOCK;
    block_node->children = NULL;
    block_node->child_count = 0;

    add_children(function_declaration_node, block_node);

    return block_node;
}

ASTNode *create_function_call_node(ASTNode *block_node, char *identifier) {
    ASTNode *function_call_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(function_call_node == NULL) {
        fprintf(stderr, "Error: failed to init function call node\n");
        exit(EXIT_FAILURE);
    }

    function_call_node->type = NODE_FUNCTION_CALL;
    function_call_node->children = NULL;
    function_call_node->child_count = 0;
    function_call_node->function_call_node.identifier = strdup(identifier);

    add_children(block_node, function_call_node);

    return function_call_node;
}

ASTNode *create_argument_node(ASTNode *function_call_node) {
    ASTNode *argument_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(argument_node == NULL) {
        fprintf(stderr, "Error: failed to create argument node\n");
        exit(EXIT_FAILURE);
    }

    argument_node->type = NODE_ARGUMENT;
    argument_node->children = NULL;
    argument_node->child_count = 0;

    add_children(function_call_node, argument_node);

    return argument_node;
}

ASTNode *create_string_literal_node(ASTNode *argument_node, char *value) {
    ASTNode *string_literal_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(string_literal_node == NULL) {
        fprintf(stderr, "Error: failed to create string literal\n");
        exit(EXIT_FAILURE);
    }

    string_literal_node->type = NODE_STRING_LITERAL;
    string_literal_node->string_literal.value = strdup(value);
    string_literal_node->children = NULL;
    string_literal_node->child_count = 0;

    add_children(argument_node, string_literal_node);

    return string_literal_node;
}

void free_node(ASTNode *node) {
    if(node == NULL) return;

    for(int i = 0; i < node->child_count; i++) {
        free_node(node->children[i]);
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