#include "../../include/parser.h"
#include "../../include/memory.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

ASTNode *parseIdentifier(Parser *p, Lexer *l, char *name);
ASTNode *parseBinary(Parser *p, Lexer *l, char *op);
ASTNode *parseUnary(Parser *p, Lexer *l, char *op);
ASTNode *parseTernary(Parser *p, Lexer *l);
ASTNode *parseGrouping(Parser *p, Lexer *l);
ASTNode *parserFunctionCall(Parser *p, Lexer *l, char *function_name, int arg_count);

ASTNode *parseLiteral(Parser *p, Lexer *l) {
    ASTNode *literal_node = NULL;

    switch(p->current.type) {
        case TOK_INT:
            int *int_value = (int*)malloc(sizeof(int));
            *int_value = atoi(p->current.lexeme);
            createLiteralNode(&literal_node, LITERAL_INT, int_value);
            eatToken(p,l,TOK_INT);
        break;

        case TOK_CHAR:
            char *char_value = (char*)malloc(sizeof(char));
            *char_value = p->current.lexeme[0];
            createLiteralNode(&literal_node, LITERAL_CHAR, char_value);
            eatToken(p,l,TOK_CHAR);
        break;
    }

    return literal_node;
}