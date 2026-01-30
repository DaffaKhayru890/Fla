#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_string_literal_node(char *value) {
    ASTNode *string_literal_node = (ASTNode*)malloc(sizeof(ASTNode));

    if(string_literal_node == NULL) {
        fprintf(stderr, "Error: failed to create string literal\n");
        exit(EXIT_FAILURE);
    }

    string_literal_node->type = NODE_STRING_LITERAL;
    string_literal_node->string_literal.value = strdup(value);
    string_literal_node->children = NULL;
    string_literal_node->child_count = 0;

    return string_literal_node;
}