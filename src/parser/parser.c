#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

Parser *init_parser(Lexer *l) {
    Parser *parser = (Parser*)malloc(sizeof(Parser));

    if(parser == NULL) {
        fprintf(stderr, "Error: failed to init parser\n");
        exit(EXIT_FAILURE);
    }

    parser->lexer = l;
    parser->current = tokenize(l);
    parser->peek = tokenize(l);

    return parser;
}

ASTNode *parser_program(Parser *p, Lexer *l, char *name) {
    ASTNode *program = create_program_node(name);

    ASTNode *parse_module = parser_module(p, l, name);
    add_child_to_parent_children(program, parse_module);
    
    return program;
}

ASTNode *parser_module(Parser *p, Lexer *l, char *name) {
    ASTNode *module = create_module_node(name);

    switch(p->current->type) {
        case TK_KEYWORD_FUN:
            ASTNode *function_declaration = parser_function_declaration(p, l);
            add_child_to_parent_children(module, function_declaration);
        break;

        // case TK_IDENTIFIER:
        //     ASTNode *function_call = parser_function_call(p, l);
        //     add_child_to_parent_children(module, function_call);
        // break;
    }

    return module;
}

void free_parser(Parser *p) {
    if(p != NULL) {
        if(p->current != NULL) {
            free(p->current);
        }else if(p->peek != NULL) {
            free(p->lexer);
        }
        
        free(p);
    }

    return;
}

void eat_token(Parser *p, TokenType type, Lexer *l) {
    if(p->current->type == type) {
        free(p->current);

        p->current = p->peek;
        p->peek = tokenize(l);
    }
    // }else {
    //     fprintf(stderr, "Error: parse failed, expected type %s, but get %s\n", token_names[type], token_names[p->current->type]);
    //     exit(EXIT_FAILURE);
    // }
}