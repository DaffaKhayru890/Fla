#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_string_literal(Parser *p, Lexer *l, Token *t) {
    char string_literal_value[256];
    strcpy(string_literal_value, p->current->literal);

    ASTNode *string_literal = create_argument_node(string_literal_value);

    eat_token(p, TK_STRING, l, t);
    eat_token(p, TK_RPAREN, l, t);
    eat_token(p, TK_KEYWORD_END, l, t);

    return string_literal;
}