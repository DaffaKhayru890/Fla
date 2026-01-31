#include "../include/lexer.h"
#include "stdio.h"
#include "../include/parser.h"
#include "../src/utils/utils.c"
#include <time.h>

void print_ast(ASTNode *node, int indent) {
    for(int i = 0; i < indent; i++) {
        printf("  ");
    }

    switch(node->type) {
        case NODE_PROGRAM:
            printf("PROGRAM:\n");

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 1);
            }
        break;

        case NODE_MODULE:
            printf("MODULE: (name: %s)\n", node->module.name);

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 1);
            }
        break;

        case NODE_FUNCTION_DECLARATION:
            printf("FUNCTION DECLARATION: (identifier: %s, return_type: %s)\n", node->function_declaration.identifier, node->function_declaration.return_type);

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 1);
            }
        break;

        case NODE_BLOCK:
            printf("BLOCK:\n");

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 1);
            }
        break;

        case NODE_FUNCTION_CALL:
            printf("FUNCTION CALL: (identifier: %s)\n", node->function_call_node.identifier);

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 1);
            }
        break;

        case NODE_ARGUMENT:
            printf("ARGUMENT:\n");

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 1);
            }
        break;

        case NODE_STRING_LITERAL:
            printf("STRING LITERAL: (value: %s):\n", node->string_literal.value);
        break;
    }
}

int main() {
     clock_t t0, t1;

    t0 = clock();
    char *source_code = read_file("../example/main.fla");

    Lexer *lexer = init_lexer(source_code);

    Parser *parser = init_parser(lexer);

    ASTNode *program_node = parser_program(parser, lexer);

    print_ast(program_node, 1);

    free_lexer(lexer);
    free_ast_node(program_node);
    free_parser(parser);

    t1 = clock();
    printf("\n%.6f seconds\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

    return 0;
};