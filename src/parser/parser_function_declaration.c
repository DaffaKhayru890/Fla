#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_function_declaration(Parser *p, Lexer *l) {
    eat_token(p, TK_KEYWORD_FUN, l);
    
    char function_name[256]; 
    strcpy(function_name, p->current->literal);

    eat_token(p, TK_IDENTIFIER, l);
    
    // Expect: ( ) ->
    eat_token(p, TK_LPAREN, l);
    eat_token(p, TK_RPAREN, l);
    eat_token(p, TK_RARROW, l);

    char return_type[256]; 
    strcpy(return_type, p->current->literal);
    
    ASTNode *function_declaration = create_function_declaration_node(function_name, p->current->literal);;

    if(strcmp(p->current->literal, "void") == 0) {
        eat_token(p, TK_KEYWORD_VOID, l);
    }

    switch(p->current->type) {
        case TK_KEYWORD_DO:
            ASTNode *block = parser_block(p, l);
            add_child_to_parent_children(function_declaration, block);
        break;
    }

    return function_declaration;
}