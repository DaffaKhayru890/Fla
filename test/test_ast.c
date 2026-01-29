#include "../include/ast.h"
#include "stdio.h"

void print_ast(ASTNode *node, int indent) {
    if(node == NULL) return;

    for(int i = 0; i < indent; i++) printf(" "); 

    switch(node->type) {
        case NODE_ROOT:
            printf("ROOT:\n");

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 3);
            }
        break;

        case NODE_MODULE:
            printf("MODULE: (name: %s)\n", node->module.name);

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 3);
            }
        break;

        case NODE_FUNCTION_DECLARATION:
            printf("FUNCTION DECLARATION: (name: %s, return type: %s)\n", node->function_declaration.identifier, node->function_declaration.return_type);

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 3);
            }
        break;

        case NODE_BLOCK:
            printf("BLOCK:\n");

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 3);
            }
        break;

        case NODE_FUNCTION_CALL:
            printf("FUNCTION CALL:\n");

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 3);
            }
        break;

        case NODE_ARGUMENT:
            printf("ARGUMENT:\n");

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 3);
            }
        break;

        case NODE_STRING_LITERAL:
            printf("STRING LITERAL: (value: %s)\n", node->string_literal.value);
        break;

        default:
            printf("END");
    }
}

int main() {
     printf("======== AST ========\n");

    ASTNode *root = create_root_node();
    ASTNode *program = create_module_node(root, "main");
    ASTNode *function = create_function_declaration_node(program, NULL,"main", "void");
    ASTNode *block = create_block_node(function);
    ASTNode *argument = create_argument_node(block);
    ASTNode *string = create_string_literal_node(argument, "Hello");

    print_ast(root, 0);

    // free_ast(root, program, function_satu, block, statement, expression);

    return 0;
};