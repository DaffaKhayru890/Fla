#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_function_declaration(Parser *p, Lexer *l) {
    eat_token(p, TK_KEYWORD_FUN, l);

    char *function_identifier = strdup(p->current->literal);

    eat_token(p, TK_IDENTIFIER, l);

    eat_token(p, TK_LPAREN, l);

    while(p->current->type != TK_RPAREN) {
        char *parameter_name = strdup(p->current->literal);
        eat(p, TK_IDENTIFIER, l);

        eat_token(p, TK_COLON, l);

        char *parameter_type;

        switch(p->current->type) {
            case TK_KEYWORD_INT:
                parameter_type = strdup(p->current->literal);
                eat_token(p, TK_KEYWORD_INT, l);
            break;

            case TK_KEYWORD_STRING:
                parameter_type = strdup(p->current->literal);
                eat_token(p, TK_KEYWORD_STRING, l);
            break;

            case TK_KEYWORD_DOUBLE:
                parameter_type = strdup(p->current->literal);
                eat_token(p, TK_KEYWORD_DOUBLE, l);
            break;

            case TK_KEYWORD_BOOLEAN:
                parameter_type = strdup(p->current->literal);
                eat_token(p, TK_KEYWORD_BOOLEAN, l);
            break;

            case TK_KEYWORD_CHAR:
                parameter_type = strdup(p->current->literal);
                eat_token(p, TK_KEYWORD_CHAR, l);
            break;
        }

        ASTNode *parameters = create_paremeter_node(parameter_name, parameter_type);

        parameters = realloc(
            parameters,
            sizeof(ASTNode*) * (parameters->expression.Parameter.parameter_count + 1)
        );
        parameters->children[parameters->expression.Parameter.parameter_count++] = parameters;

        if(p->current->type == TK_COMMA) {
            eat_token(p, TK_COMMA, l);
        }

        free(parameter_name);
        free(parameter_type);
    }

    eat_token(p, TK_RPAREN, l);

    eat_token(p, TK_RARROW, l);

    char *return_type = strdup(p->current->literal);

    ASTNode *function_declaration = create_function_declaration_node(function_identifier, return_type);

    switch(p->current->type) {
        case TK_KEYWORD_DO:
            ASTNode *block = parser_block(p, l);
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

    ASTNode *block = create_block_node();

    while(p->current->type != TK_KEYWORD_END) {
        switch(p->current->type) {
            case TK_KEYWORD_VAR:
                ASTNode *variable_declaration = parser_variable_declaration(p, l);
                add_child_to_parent_children(block, variable_declaration);
            break;
        }
    }

    return block;
}

ASTNode *parser_variable_declaration(Parser *p, Lexer *l) {
    eat_token(p, TK_KEYWORD_VAR, l);

    char *name = strdup(p->current->literal);

    eat_token(p, TK_IDENTIFIER, l);

    eat_token(p, TK_COLON, l);

    char *type = strdup(p->current->literal);

    switch(p->current->type) {
        case TK_KEYWORD_INT:
            eat_token(p, TK_KEYWORD_INT, l);
        break;

        case TK_KEYWORD_DOUBLE:
            eat_token(p, TK_KEYWORD_DOUBLE, l);
        break;

        case TK_KEYWORD_CHAR:       
            eat_token(p, TK_KEYWORD_CHAR, l);
        break;

        case TK_KEYWORD_STRING:
            eat_token(p, TK_KEYWORD_STRING, l);
        break;

        case TK_KEYWORD_BOOLEAN:
            eat_token(p, TK_KEYWORD_BOOLEAN, l);
        break;
    }

    ASTNode *variable_declaration = create_variable_declaration_node(name, type);

    if(p->current->type == TK_ASSIGN) {
        eat_token(p, TK_ASSIGN, l);

        ASTNode *literal = parser_literal(p, l);
        add_child_to_parent_child(variable_declaration, literal);
    }else {

    }

    free(name);
    free(type);

    return variable_declaration;
};

ASTNode *parser_if(Parser *p, Lexer *l);
ASTNode *parser_while(Parser *p, Lexer *l);
ASTNode *parser_for(Parser *p, Lexer *l);
ASTNode *parser_switch(Parser *p, Lexer *l);