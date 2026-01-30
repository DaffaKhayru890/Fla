#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_program(Parser *p, Lexer *l, Token *t) {
    ASTNode *program = create_program_node();

    printf("%s\n", p->current->literal);

    while(p->current->type != TK_EOF) {
        ASTNode *parse_module = parser_module(p, l, t);
        add_child_to_parent_children(program, parse_module);
    }
    
    return program;
}