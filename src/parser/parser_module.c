#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "../../include/parser.h"

ASTNode *parser_module(Parser *p, Lexer *l) {
    ASTNode *module = create_module_node("main");

    switch(p->current->type) {
        case TK_KEYWORD_FUN:
            ASTNode *function_declaration = parser_function_declaration(p, l);
            add_child_to_parent_children(module, function_declaration);
        break;
    }

    return module;
}