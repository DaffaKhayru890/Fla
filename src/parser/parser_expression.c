#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_binary(Parser *p, Lexer *l);
ASTNode *parser_function_call(Parser *p, Lexer *l);

ASTNode *parser_literal(Parser *p, Lexer *l) {
    ASTNode *literal = NULL;

    switch(p->current->type) {
        case TK_NUMBER:
            literal = create_literal_node(
                LITERAL_INT,
                atoi(p->current->literal),
                0.0,
                '\0',
                NULL,
                false
            );
            
            eat_token(p, TK_NUMBER, l);
        break;

        case TK_STRING:
            literal = create_literal_node(
                LITERAL_INT,
                0,
                0.0,
                '\0',
                strdup(p->current->literal),
                false
            );
            
            eat_token(p, TK_STRING, l);
        break;

        case TK_CHAR:
            literal = create_literal_node(
                LITERAL_INT,
                0,
                0.0,
                p->current->literal,
                NULL,
                false
            );
            
            eat_token(p, TK_KEYWORD_INT, l);
        break;

        case TK_KEYWORD_FALSE:
            literal = create_literal_node(
                LITERAL_INT,
                0,
                0.0,
                '\0',
                NULL,
                (p->current->type == TK_KEYWORD_TRUE)
            );
            
            eat_token(p, TK_KEYWORD_BOOLEAN, l);
        break;
    }

    return literal;
}

ASTNode *parser_unary(Parser *p, Lexer *l){}

ASTNode *parser_assignment(Parser *p, Lexer *l) {

}

ASTNode *parser_paremeter(Parser *p, Lexer *l){}