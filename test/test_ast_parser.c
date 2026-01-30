#include "../include/ast.h"
#include "../include/lexer.h"
#include "stdio.h"
#include "../include/parser.h"
#include "../src/utils/utils.c"

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
            printf("PROGRAM: (name: %s)\n", node->module.name);

            for(int i = 0; i < node->child_count; i++) {
                print_ast(node->children[i], indent + 1);
            }
        break;

        case NODE_FUNCTION_DECLARATION:
            printf("FUNCTION DECLARATION: (identifier: %s, return_type%s)\n", node->function_declaration.identifier, node->function_declaration.return_type);

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
    char *source_code = read_file("../example/main.fla");

    Lexer *lexer = init_lexer(source_code);
    Token *token = init_token();

    Parser *parser = init_parser(lexer, token);

    ASTNode *program_node = parser_program(parser, lexer, token);

    print_ast(program_node, 1);

    free_lexer(lexer);
    free_token(token);
    free_ast_node(program_node);
    free_parser(parser);

    return 0;
};