#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_block(Parser *p, Lexer *l, Token *t) {
    ASTNode *block = create_block_node();

    // do keyword
    eat_token(p, TK_KEYWORD_DO, l, t);

    // current 
    switch(p->current->type) {
        case TK_IDENTIFIER:
            ASTNode *function_call = parser_function_call(p, l, t);
            add_child_to_parent_children(block, function_call);
        break;
    }

    return block;
}