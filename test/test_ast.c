#include "../include/ast.h"
#include "stdio.h"

int main() {
    ASTNode *root = create_root_node();
    ASTNode *program = create_program_node(root);
    ASTNode *function_satu = create_function_node(program, "main", "int");
    ASTNode *function_dua = create_function_node(program, "coba", "void");
    ASTNode *block = create_block_node(function_satu);
    ASTNode *statement = create_statement_node(block);
    ASTNode *expression = create_expression_node(statement, 0);


    printf("======== AST ========\n");

    print_ast(root, 0);

    free_ast(root, program, function_satu, block, statement, expression);

    return 0;
};