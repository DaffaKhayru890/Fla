#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_node(NodeType node_type) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));

    if(node == NULL) {
        fprintf(stderr, "Error: failed to create new node");
        exit(EXIT_FAILURE);
    };

    node->type = node_type;

    return node;
}

ASTNode *create_program_node() {
    ASTNode *root = create_node(NODE_PROGRAM);

    root->child_count = 0;
    root->children = NULL;
    root->child_count = 0;

    return root;
}

ASTNode *create_module_node(char *name) {
    ASTNode *module = create_node(NODE_MODULE);

    module->module.name = strdup(name);
    module->children = NULL;
    module->child_count = 0;

    return module;
}

void add_child_to_parent_child(ASTNode *parent, ASTNode* child) {
    if(parent == NULL || child == NULL) return;

    parent->child = child;
}

void add_child_to_parent_children(ASTNode *parent, ASTNode* child) {
    if(parent == NULL || child == NULL) return;
    
    ASTNode **new_children = (ASTNode**)realloc(
        parent->children,
        sizeof(ASTNode*) * (parent->child_count + 1)
    );

    if(new_children == NULL) {
        fprintf(stderr, "Error: failed to add children");
        exit(EXIT_FAILURE);
    };

    parent->children = new_children;
    parent->children[parent->child_count] = child;
    parent->child_count += 1;
}

void free_node(ASTNode *node) {
    if(node == NULL) return;

    for(int i = 0; i < node->child_count; i++) {
        free(node->children[i]);
    }

    if(node->children != NULL) {
        free(node->children);
    }

    switch(node->type) {
        case NODE_PROGRAM:
            free(node);
        break;

        case NODE_MODULE:
            if (node->module.name) {
                free(node->module.name);
            }
        break;

        case NODE_STATEMENT:
            free_statement(node);
            break;
            
        case NODE_EXPRESSION:
            free_expression(node);
            break;
    }
}

void free_statement(ASTNode *node) {
    if(node == NULL) return;

    for(int i = 0; i < node->child_count; i++) {
        free(node->children[i]);
    }

    if(node->children != NULL) {
        free(node->children);
    }

    switch(node->statement.statement_kind) {
        case STATEMENT_FUNCTION_DECLARATION:
            if(node->statement.FunctionDeclaration.name) {
                free(node->statement.FunctionDeclaration.name);
                
            }else if(node->statement.FunctionDeclaration.return_type) {
                free(node->statement.FunctionDeclaration.return_type);
            }
        break;

        case STATEMENT_VARIABLE_DECLARATION:
            if(node->statement.VariableDeclaration.name) {
                free(node->statement.VariableDeclaration.name);
            }
        break;
    }
}

void free_expression(ASTNode *node) {
    if(node == NULL) return;

    for(int i = 0; i < node->child_count; i++) {
        free(node->children[i]);
    }

    if(node->children != NULL) {
        free(node->children);
    }

    switch(node->expression.expression_kind) {
        case EXPRESSION_BINARY:
            if(node->expression.Binary.operator) {
                free(node->expression.Binary.operator);
            } 
        break;
    }

    switch(node->expression.Literal.literal_kind) {
        case LITERAL_STRING:
            if(node->expression.Literal.string_value) {
                free(node->expression.Literal.string_value);
            }
        break;
    }
}