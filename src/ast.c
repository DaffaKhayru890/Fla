#include "../include/ast.h"
#include "stdio.h"
#include "stdlib.h"

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

ASTNode *create_program_node(ASTNode *root_node) {
    ASTNode *program_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(program_node == NULL) {
        perror("Failed initialize rood node");
    }

    program_node->type = NODE_PROGRAM;
    program_node->program.children = NULL;
    program_node->program.child_count = 0;

    root_node->children = realloc(
        root_node->children,
        sizeof(ASTNode*) * (root_node->child_count + 1)
    );
    root_node->children[root_node->child_count] = program_node;
    root_node->child_count += 1;

    return program_node;
}

ASTNode* create_function_node(ASTNode *program_node, char *identifier, char *return_type) {
    ASTNode *function_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(function_node == NULL) {
        perror("Failed initialize rood node");
    }

    function_node->type = NODE_FUNCTION;
    function_node->function.identifier = identifier;
    function_node->function.return_type = return_type;
    function_node->function.children = NULL;
    function_node->function.child_count = 0;

    program_node->program.children = (ASTNode**)realloc(
        program_node->program.children,
        sizeof(ASTNode*) * (program_node->child_count + 1)
    );
    program_node->program.children[program_node->program.child_count] = function_node;
    program_node->program.child_count += 1;

    return function_node;
}

ASTNode *create_block_node(ASTNode *function_node) {
    ASTNode *block_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(block_node == NULL) {
        perror("Failed initialize rood node");
    }

    block_node->type = NODE_BLOCK;
    block_node->block.children = NULL;
    block_node->block.child_count = 0;

    function_node->function.children = realloc(
        function_node->function.children,
        sizeof(ASTNode*) * (function_node->function.child_count + 1)
    ); 
    function_node->function.children[function_node->function.child_count] = block_node;
    function_node->function.child_count += 1;

    return block_node;
}

ASTNode *create_statement_node(ASTNode *block_node) {
    ASTNode *statement_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(statement_node == NULL) {
        perror("Failed initialize rood node");
    }

    statement_node->type = NODE_STATEMENT;
    statement_node->statement.child = NULL;
    
    block_node->block.children = realloc(
        block_node->block.children,
        sizeof(ASTNode*) * (block_node->block.child_count + 1)
    );
    block_node->block.children[block_node->block.child_count] = statement_node;
    block_node->block.child_count += 1;

    return statement_node;
}

ASTNode *create_expression_node(ASTNode *statement_node, int value) {
    ASTNode *expression_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(expression_node == NULL) {
        perror("Failed initialize rood node");
    }

    expression_node->type = NODE_EXPRESSION;
    expression_node->expression.value_int = value;

    statement_node->statement.child = malloc(sizeof(ASTNode));
    statement_node->statement.child = expression_node;

    return expression_node;
}

void free_ast(
    ASTNode *root_node,
    ASTNode *program_node, 
    ASTNode *function_node, 
    ASTNode *block_node, 
    ASTNode *statement_node,
    ASTNode *expression_node
) {
    if(!root_node && !program_node && !function_node && !block_node && !statement_node && !expression_node) {
        free(root_node);
        free(program_node);
    }
}

void print_ast(ASTNode *node, int indent) {
    if(node == NULL) return;

    for(int i = 0; i < indent; i++) printf(" "); 

    switch(node->type) {
        case NODE_ROOT:
            printf("ROOT:\n");

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 1);
            }
        break;

        case NODE_PROGRAM:
            printf("PROGRAM:\n");

            for(int i = 0; i < node->program.child_count; i++) {
                print_ast(node->program.children[i], indent + 1);
            }
        break;

        case NODE_FUNCTION:
            printf("FUNCTION: (identifier: %s, return_type: %s)\n", node->function.identifier, node->function.return_type);

            for(int i = 0; i < node->function.child_count; i++) {
                print_ast(node->function.children[i], indent + 1);
            }
        break;

        case NODE_BLOCK:
            printf("BLOCK: \n");

            for(int i = 0; i < node->block.child_count; i++) {
                print_ast(node->block.children[i], indent + 1);
            }
        break;

        case NODE_STATEMENT:
            printf("STATEMENT: \n");

            print_ast(node->statement.child, indent + 1);
        break;

        case NODE_EXPRESSION:
            printf("EXPRESSION: (value: %d)\n", node->expression.value_int);

            print_ast(node->statement.child, indent + 1);
        break;

        default:
            printf("END");
    }
}