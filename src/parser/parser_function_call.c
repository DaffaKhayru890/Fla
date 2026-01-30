#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_function_call(Parser *p, Lexer *l, Token *t) {
    char function_call_identifier[256];
    strcpy(function_call_identifier, p->current->literal); 

    ASTNode *function_call = create_function_call_node(function_call_identifier);

    switch(p->current->type) {
        case TK_IDENTIFIER:
            // identifier 
            eat_token(p, TK_IDENTIFIER, l, t);
            eat_token(p, TK_LPAREN, l, t);

            ASTNode *argument = parser_argument(p, l, t);
            add_child_to_parent_children(function_call, argument);
        break;
    }

    return function_call;
}