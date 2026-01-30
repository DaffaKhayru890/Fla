#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

Parser *init_parser(Lexer *l, Token *t) {
    Parser *parser = (Parser*)malloc(sizeof(Parser));

    if(parser == NULL) {
        fprintf(stderr, "Error: failed to init parser\n");
        exit(EXIT_FAILURE);
    }

    parser->lexer = l;
    parser->current = tokenize(l,t);

    return parser;
}

Token *current_token(Parser *p) {
    return p->current;
}

bool check_token(Parser *p, TokenType type) {
    if(p->current->type == type) {
        return true;
    }

    return false;
}

void free_parser(Parser *p) {
    if(p != NULL) {
        free(p);
    }

    return;
} 

void eat_token(Parser *p, TokenType type, Lexer *l, Token *t) {
    if(p->current->type == type) {
        free(p->current);
        p->current = tokenize(l,t);
    }else {
        fprintf(stderr, "Error: parse failed, expected type%d, but get %d\n", p->current->type, type);
        exit(EXIT_FAILURE);
    }
}

ASTNode *parser_module(ASTNode *root_node, Parser *p, Lexer *l, Token *t) {
    if (root_node == NULL) {
        fprintf(stderr, "Error: root node not found\n");
        exit(EXIT_FAILURE);
    }

    eat_token(p, TK_KEYWORD , l, t);
    char *module_name = t->literal;


    ASTNode *module = create_module_node(root_node, module_name);

    eat_token(p, p->current->type, l, t);
    
    return  module;
}

ASTNode *parser_function_declaration(ASTNode *module_node, Parser *p, Lexer *l, Token *t) {
    if (module_node == NULL) {
        fprintf(stderr, "Error: module node node not found\n");
        exit(EXIT_FAILURE);
    }

    eat_token(p, TK_KEYWORD , l, t);
    char *function_declaration_name = t->literal;

    eat_token(p, TK_IDENTIFIER , l, t);
    eat_token(p, TK_RARROW , l, t);
    

    ASTNode *function_declration = create_function_declaration_node(module_name, NULL, function_declaration_name, );

    eat_token(p, p->current->type, l, t);
    
    return  module;
}