#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_function_call(Parser *p, Lexer *l) {
    char function_call_identifier[256];
    strcpy(function_call_identifier, p->current->literal); 

    ASTNode *function_call = create_function_call_node(function_call_identifier);

    switch(p->current->type) {
        case TK_IDENTIFIER:
            eat_token(p, TK_IDENTIFIER, l);
            eat_token(p, TK_LPAREN, l);

            ASTNode *argument = parser_argument(p, l);
            add_child_to_parent_children(function_call, argument);

            eat_token(p, TK_RPAREN, l);
            // eat_token(p, TK_KEYWORD_END, l, t);
        break;
    }

    return function_call;
}