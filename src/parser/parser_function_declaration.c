#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_function_declaration(Parser *p, Lexer *l, Token *t) {
    printf("identifier function decl: %s\n", t->literal);
    
    // fun keyword
    eat_token(p, TK_KEYWORD_FUN, l, t);
    
    char function_name[256]; 
    strcpy(function_name, p->current->literal);
    
    ASTNode *function_declaration = create_function_declaration_node(function_name, p->peek->literal);

    // function identifier or name
    eat_token(p, TK_IDENTIFIER, l, t);

    // ( lparen
    eat_token(p, TK_LPAREN, l, t);
    
    // ) rparen
    eat_token(p, TK_RPAREN, l, t);

    // -> rarrow
    eat_token(p, TK_RARROW, l, t);

    // current node is do
    switch(p->current->type) {
        case TK_KEYWORD_DO:
            ASTNode *block = parser_block(p, l, t);
            add_child_to_parent_children(function_declaration, block);
        break;
    }

    return function_declaration;
}