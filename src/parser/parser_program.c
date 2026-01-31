#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_program(Parser *p, Lexer *l) {
    ASTNode *program = create_program_node();

    ASTNode *parse_module = parser_module(p, l);
    add_child_to_parent_children(program, parse_module);
    
    return program;
}