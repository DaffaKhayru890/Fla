#include "../../include/parser.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

ASTNode *parseFuncDecl(Parser *p, Lexer *l) {
    ASTNode **params_node = NULL;
    ASTNode *func_decl_node = NULL;

    char *func_identifier = NULL;
    ReturnType return_type;

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
            return_type = RETURN_TYPE_INT;
            eatToken(p,l,TOK_TYPE_INT);
        break;

        case TOK_TYPE_DOUBLE:
            return_type = RETURN_TYPE_DOUBLE;
            eatToken(p,l,TOK_TYPE_DOUBLE);
        break;

        case TOK_TYPE_VOID:
            return_type = RETURN_TYPE_VOID;
            eatToken(p,l,TOK_TYPE_VOID);
        break;
    }

    eatToken(p, l, TOK_LBRACE);

    createFuncDeclNode(&func_decl_node, func_identifier, return_type, params_count);

    func_decl_node->function_delcaration.parameters = params_node;

    func_decl_node->function_delcaration.body = parseBlock(p, l);

    bool is_void = return_type == RETURN_TYPE_VOID;

    if(!is_void) {
        bool has_return = hasReturnStatment(func_decl_node->function_delcaration.body);

        if(!has_return) {
            fprintf(stderr, "Error: no return statement\n");
            exit(EXIT_FAILURE);
        }
    }

    free(func_identifier);

    return func_decl_node;
}

ASTNode *parseBlock(Parser *p, Lexer *l) {
    int statements_count = 0;
    int statements_capacity = 4;
    
    ASTNode *block_node = NULL;
    
    createBlockNode(&block_node, statements_count);

    block_node->block_statement.statements = (ASTNode**)malloc(sizeof(ASTNode*) * statements_capacity);

    while(p->current.type != TOK_RBRACE && p->current.type != TOK_EOF) {
        ASTNode *statement_node = NULL;
        
        switch(p->current.type) {
            case TOK_IDENTIFIER:
                statement_node = parserFunctionCall(p,l);
            break;

            case TOK_KEY_VAR:
                statement_node = parseVarDecl(p,l);
            break;

            case TOK_KEY_CONST:
                statement_node = parseVarDecl(p,l);
            break;

            case TOK_KEY_RETURN:
                statement_node = parseReturn(p,l);
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

    VarType variable_type;

    if(match(p, TOK_KEY_VAR)) {
        eatToken(p,l,TOK_KEY_VAR);
        variable_type = VARIABLE_TYPE_VAR;
    }else if(match(p, TOK_KEY_CONST)) {
        eatToken(p,l,TOK_KEY_CONST);
        variable_type = VARIABLE_TYPE_CONST;
    }
    
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

    createVarDeclNode(&var_decl_node, var_identifier, var_type, variable_type);
    
    free(var_identifier);
    free(var_type);

    if(match(p, TOK_SEMICOLON)) {
        eatToken(p,l,TOK_SEMICOLON);
        
        var_decl_node->variable_declaration.init = NULL;

        if(var_decl_node->variable_declaration.variable_type == VARIABLE_TYPE_CONST) {
            fprintf(stderr, "Error: const variable must be initialized\n");
            exit(EXIT_FAILURE);
        }

        return var_decl_node;
    }else {
        if(p->next.type == TOK_IDENTIFIER) {
            eatToken(p,l,TOK_ASSIGNMENT);
            var_decl_node->variable_declaration.init = parserVariableCall(p,l);
            eatToken(p,l,TOK_SEMICOLON);
            return var_decl_node;
        }else {
            eatToken(p,l,TOK_ASSIGNMENT);
            var_decl_node->variable_declaration.init = parseExpression(p,l,PREC_NONE);
            eatToken(p,l,TOK_SEMICOLON);
            return var_decl_node;
        }
    }
}

ASTNode *parseIf(Parser *p, Lexer *l);
ASTNode *parseWhile(Parser *p, Lexer *l);
ASTNode *parseFor(Parser *p, Lexer *l);
ASTNode *parseSwitch(Parser *p, Lexer *l);

ASTNode *parseReturn(Parser *p, Lexer *l) {
    ASTNode *return_node = NULL;
    ASTNode *literal_node = NULL;

    createReturnNode(&return_node);

    eatToken(p,l,TOK_KEY_RETURN);

    return_node->return_function.expression = (ASTNode*)malloc(sizeof(ASTNode));
    
    literal_node = parseLiteral(p,l);

    return_node->return_function.expression = literal_node;

    eatToken(p,l,TOK_SEMICOLON);

    return return_node;
}