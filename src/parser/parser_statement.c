#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_function_declaration(Parser *p, Lexer *l) {
    while(p->current->type != TK_IDENTIFIER && p->current->type != TK_EOF) {
        eat_token(p, p->current->type, l);
    }

    char function_identifier[256];
    strcpy(function_identifier, p->current->literal);

    while(p->current->type != TK_RARROW && p->current->type != TK_EOF) {
        eat_token(p, p->current->type, l);
    }

    // printf("%s %s", p->current->literal, p->peek->literal);

    char return_type[256];
    strcpy(return_type, p->peek->literal);

    ASTNode *function_declaration = create_function_declaration_node(function_identifier, return_type);

    while(p->current->type != TK_KEYWORD_DO && p->current->type != TK_EOF) {
        eat_token(p, p->current->type, l);
    }

    switch(p->current->type) {
        case TK_KEYWORD_DO:
            ASTNode *block = create_block_node();
            add_child_to_parent_children(function_declaration, block);
        break;
    }

    eat_token(p, TK_KEYWORD_END, l);

    free(function_identifier);
    free(return_type);
    
    return function_declaration;
}

ASTNode *parser_block(Parser *p, Lexer *l) {
    eat_token(p, TK_KEYWORD_DO, l);

    // switch(p->current->type) {
    //     case :
    // }
}

ASTNode *parser_variable_declaration(Parser *p, Lexer *l) {

};

ASTNode *parser_if(Parser *p, Lexer *l);
ASTNode *parser_while(Parser *p, Lexer *l);
ASTNode *parser_for(Parser *p, Lexer *l);
ASTNode *parser_switch(Parser *p, Lexer *l);