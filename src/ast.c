#include "../include/ast.h"
#include "stdio.h"
#include "stdlib.h"

void add_children(ASTNode *parent_node, ASTNode *child_node) {
    parent_node->children = realloc(
        parent_node->children,
        sizeof(ASTNode*) * (parent_node->child_count + 1)
    );
    parent_node->children[parent_node->child_count] = child_node;
    parent_node->child_count += 1;
}

ASTNode *create_root_node(void) {
    ASTNode *root_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(root_node == NULL) {
        perror("Failed initialize rood node");
    }

    root_node->type = NODE_ROOT;
    root_node->children = NULL;
    root_node->child_count = 0;
    
    return root_node;
};

ASTNode *create_module_node(ASTNode *root_node, char *name) {
    ASTNode *module_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(module_node == NULL) {
        perror("Failed initialize rood node");
    }

    module_node->type = NODE_MODULE;
    module_node->module.name = name;
    module_node->children = NULL;
    module_node->child_count = 0;

    add_children(root_node, module_node);

    return module_node;
}

ASTNode* create_function_declaration_node(ASTNode *module_node, ASTNode *class_node, char *identifier, char *return_type) {
    ASTNode *function_declaration_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(function_declaration_node == NULL) {
        perror("Failed initialize rood node");
    }

    function_declaration_node->type = NODE_FUNCTION_DECLARATION;
    function_declaration_node->function_declaration.identifier = identifier;
    function_declaration_node->function_declaration.return_type = return_type;
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
        perror("Failed initialize rood node");
    }

    block_node->type = NODE_BLOCK;
    block_node->children = NULL;
    block_node->child_count = 0;

    add_children(function_declaration_node, block_node);

    return block_node;
}

ASTNode *create_function_call_node(ASTNode *block_node) {
    ASTNode *function_call_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(function_call_node == NULL) {
        perror("Failed initialize rood node");
    }

    function_call_node->type = NODE_FUNCTION_CALL;
    function_call_node->children = NULL;
    function_call_node->child_count = 0;

    add_children(block_node, function_call_node);

    return function_call_node;
}

ASTNode *create_argument_node(ASTNode *function_call_node) {
    ASTNode *argument_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(argument_node == NULL) {
        perror("Failed initialize rood node");
    }

    argument_node->type = NODE_ARGUMENT;
    argument_node->children = NULL;
    argument_node->child_count = 0;

    add_children(function_call_node, argument_node);

    return function_call_node;
}

ASTNode *create_string_literal_node(ASTNode *argument_node, char *value) {
    ASTNode *string_literal_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(string_literal_node == NULL) {
        perror("Failed initialize rood node");
    }

    string_literal_node->type = NODE_STRING_LITERAL;
    string_literal_node->string_literal.value = value;
    string_literal_node->children = NULL;
    string_literal_node->child_count = 0;

    add_children(argument_node, string_literal_node);

    return string_literal_node;
}

void free_ast() {

}

