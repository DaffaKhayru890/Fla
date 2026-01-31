#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_string_literal(Parser *p, Lexer *l) {
    char string_literal_value[256];
    strcpy(string_literal_value, p->current->literal);

    ASTNode *string_literal = create_string_literal_node(string_literal_value);

    eat_token(p, TK_STRING, l);

    return string_literal;
}