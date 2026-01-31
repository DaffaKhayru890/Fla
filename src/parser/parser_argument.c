#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_argument(Parser *p, Lexer *l) {
    ASTNode *argument = create_argument_node();

    switch(p->current->type) {
        case TK_STRING:
            ASTNode *string_literal = parser_string_literal(p, l);
            add_child_to_parent_children(argument, string_literal);
            
        break;
    }

    return argument;
}