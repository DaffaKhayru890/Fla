#include "../../include/parser.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    int params_capacity = 4;

    params_node = (ASTNode**)malloc(sizeof(ASTNode*) * params_capacity);

    while(p->current.type != TOK_RPAREN && p->current.type != TOK_EOF) {
        char *param_identifier = NULL;
        char *param_type = NULL;

        if(match(p, TOK_IDENTIFIER)) {
            param_identifier = strdup(p->current.lexeme);
        }

        eatToken(p, l, TOK_IDENTIFIER);
        eatToken(p, l, TOK_COLON);

        switch(p->current.type) {
            case TOK_TYPE_INT:
                param_type = strdup("int");
                eatToken(p,l,TOK_TYPE_INT);
            break;

            case TOK_TYPE_DOUBLE:
                param_type = strdup("double");
                eatToken(p,l,TOK_TYPE_DOUBLE);
            break;

            case TOK_TYPE_FLOAT:
                param_type = strdup("float");
                eatToken(p,l,TOK_TYPE_FLOAT);
            break;

            case TOK_TYPE_CHAR:
                param_type = strdup("char");
                eatToken(p,l,TOK_TYPE_CHAR);
            break;
        }

        if(params_count >= params_capacity) {
            params_capacity = params_capacity * 2;
            params_node = (ASTNode**)realloc(
                params_node,
                sizeof(ASTNode*) * params_capacity
            );
        }

        ASTNode *param_node = NULL;

        createParamNode(&param_node, param_identifier, param_type);
        params_node[params_count] = param_node;
        params_count++;

        free(param_identifier);
        free(param_type);

        if(match(p, TOK_COMMA)) {
            eatToken(p, l, TOK_COMMA);
        }
    }

    eatToken(p, l, TOK_RPAREN);
    eatToken(p, l, TOK_RARROW);

    switch(p->current.type) {
        case TOK_TYPE_INT:
            func_return_type = strdup(p->current.lexeme);
            eatToken(p,l,TOK_TYPE_INT);
        break;

        case TOK_TYPE_VOID:
            func_return_type = strdup(p->current.lexeme);
            eatToken(p,l,TOK_TYPE_VOID);
        break;
    }

    eatToken(p, l, TOK_LBRACE);

    createFuncDeclNode(&func_decl_node, func_identifier, func_return_type, params_count);

    func_decl_node->function_delcaration.parameters = params_node;

    free(func_identifier);
    free(func_return_type);

    func_decl_node->function_delcaration.body = parseBlock(p, l);

    return func_decl_node;
}

ASTNode *parseReturn(Parser *p, Lexer *l);

ASTNode *parseBlock(Parser *p, Lexer *l) {
    int statements_count = 0;
    int statements_capacity = 4;
    
    ASTNode *block_node = NULL;
    
    createBlockNode(&block_node, statements_count);

    block_node->block_statement.statements = (ASTNode**)malloc(sizeof(ASTNode*) * statements_capacity);

    while(p->current.type != TOK_RBRACE && p->current.type != TOK_EOF) {
        ASTNode *statement_node = NULL;
        
        switch(p->current.type) {
            case TOK_KEY_VAR:
                statement_node = parseVarDecl(p,l);
            break;
        }

        if(statements_count >= statements_capacity) {
            statements_capacity = statements_capacity * 2;
            block_node->block_statement.statements = (ASTNode**)realloc(
                block_node->block_statement.statements,
                sizeof(ASTNode*) * statements_capacity
            );
        }

        block_node->block_statement.statements[statements_count] = statement_node;
        statements_count++;
        block_node->block_statement.statements_count = statements_count;
    }

    eatToken(p, l, TOK_RBRACE);

    return block_node;
}

ASTNode *parseVarDecl(Parser *p, Lexer *l) {
    ASTNode *var_decl_node = NULL;
    char *var_identifier = NULL;
    char *var_type = NULL;

    eatToken(p,l,TOK_KEY_VAR);

    if(match(p, TOK_IDENTIFIER)) {
        var_identifier = strdup(p->current.lexeme);
    }

    eatToken(p,l,TOK_IDENTIFIER);
    eatToken(p,l,TOK_COLON);

    if(match(p,TOK_TYPE_INT)) {
        var_type = strdup(p->current.lexeme);
        eatToken(p,l,TOK_TYPE_INT);
    }else if(match(p,TOK_TYPE_DOUBLE)) {
        var_type = strdup(p->current.lexeme);
        eatToken(p,l,TOK_TYPE_DOUBLE);
    }else if(match(p, TOK_TYPE_CHAR)) {
        var_type = strdup(p->current.lexeme);
        eatToken(p,l,TOK_TYPE_CHAR);
    }else if(match(p, TOK_TYPE_FLOAT)) {
        var_type = strdup(p->current.lexeme);
        eatToken(p,l,TOK_TYPE_FLOAT);
    }

    eatToken(p,l,TOK_ASSIGNMENT);

    createVarDeclNode(&var_decl_node, var_identifier, var_type);

    free(var_identifier);
    free(var_type);

    var_decl_node->variable_declaration.init = parseLiteral(p,l);

    eatToken(p,l,TOK_SEMICOLON);

    return var_decl_node;
}

ASTNode *parseIf(Parser *p, Lexer *l);
ASTNode *parseWhile(Parser *p, Lexer *l);
ASTNode *parseFor(Parser *p, Lexer *l);
ASTNode *parseSwitch(Parser *p, Lexer *l);