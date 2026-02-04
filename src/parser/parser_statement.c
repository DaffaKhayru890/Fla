#include "../../include/parser.h"
#include "../../include/memory.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

ASTNode *parseFuncDecl(Parser *p, Lexer *l) {
    ASTNode **params_node = NULL;
    ASTNode *func_decl_node = NULL;

    char *func_identifier = NULL;
    char *func_return_type = NULL;

    eatToken(p, l, TOK_KEY_FUN);

    if(match(p, TOK_IDENTIFIER)) {
        func_identifier = strdup(p->current.lexeme);
    }

    eatToken(p, l, TOK_IDENTIFIER);
    eatToken(p, l, TOK_LPAREN);

    int params_count = 0;
    int params_capacity = 2;

    params_node = ALLOCATE(ASTNode**, params_capacity + 1);

    while(p->current.type != TOK_RPAREN && p->current.type != TOK_EOF) {
        char *param_identifier = NULL;
        char *param_type = NULL;

        if(match(p, TOK_IDENTIFIER)) {
            param_identifier = strdup(p, p->current.lexeme);
        }

        eatToken(p, l, TOK_IDENTIFIER);
        eatToken(p, l, TOK_COLON);

        switch(p->current.type) {
            case TOK_TYPE_INT:
                param_type = strdup("int");
            break;

            case TOK_TYPE_DOUBLE:
                param_type = strdup("double");
            break;

            case TOK_TYPE_CHAR:
                param_type = strdup("char");
            break;

            case TOK_TYPE_STRING:
                param_type = strdup("string");
            break;

            case TOK_TYPE_BOOLEAN:
                param_type = strdup("boolean");
            break;
        }

        if(params_count >= params_capacity) {
            params_capacity = params_capacity * 2;
            params_node = GROW(ASTNode*, params_node, params_capacity);
        }

        ASTNode *param_node = NULL;

        createParamNode(&param_node, param_identifier, param_type);
        params_node[params_count] = param_node;
        params_count++;

        FREE(param_identifier);
        FREE(param_type);

        if(match(p, TOK_COMMA)) {
            eatToken(p, l, TOK_COMMA);
        }
    }

    eatToken(p, l, TOK_RPAREN);
    eatToken(p, l, TOK_RARROW);
    eatToken(p, l, TOK_LBRACE);

    createFuncDeclNode(&func_decl_node, func_identifier, func_return_type);

    eatToken(p, l, TOK_RBRACE);

    FREE(func_identifier);
    FREE(func_return_type);

    return func_decl_node;
}

ASTNode *parseReturn(Parser *p, Lexer *l);
ASTNode *parseBlock(Parser *p, Lexer *l);
ASTNode *parseVarDecl(Parser *p, Lexer *l);
ASTNode *parseIf(Parser *p, Lexer *l);
ASTNode *parseWhile(Parser *p, Lexer *l);
ASTNode *parseFor(Parser *p, Lexer *l);
ASTNode *parseSwitch(Parser *p, Lexer *l);