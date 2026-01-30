#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_module(Parser *p, Lexer *l, Token *t) {
    ASTNode *module = create_module_node("main");

    printf("identifier function decl: %s\n", t->literal);

    switch(p->current->type) {
        case TK_KEYWORD_FUN:
            ASTNode *function_declaration = parser_function_declaration(p, l, t);
            add_child_to_parent_children(module, function_declaration);
        break;
    }

    return module;
}