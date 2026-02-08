#include "../../include/parser.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static const char *TokenTypeString[] = {
    // base keyword
    "TOK_KEY_USE",
    "TOK_KEY_FUN",
    "TOK_KEY_RETURN",
    "TOK_KEY_VAR",
    "TOK_KEY_CONST",
    "TOK_KEY_IF",
    "TOK_KEY_ELSE",
    "TOK_KEY_BREAK",
    "TOK_KEY_CONTINUE",
    "TOK_KEY_WHILE",
    "TOK_KEY_FOR",
    "TOK_KEY_SWITCH",
    "TOK_KEY_TRUE",
    "TOK_KEY_FALSE",

    // delimiters
    "TOK_LPAREN",
    "TOK_RPAREN",
    "TOK_LBRACE",
    "TOK_RBRACE",
    "TOK_LBRACKETS",
    "TOK_RBRACKETS",

    // unique
    "TOK_IDENTIFIER",

    // type keyword
    "TOK_TYPE_INT",
    "TOK_TYPE_DOUBLE",
    "TOK_TYPE_CHAR",
    "TOK_TYPE_FLOAT",
    "TOK_TYPE_BOOLEAN",
    "TOK_TYPE_STRING",
    "TOK_TYPE_VOID",

    // basic operators
    "TOK_PLUS",
    "TOK_MINUS",
    "TOK_MULTIPLY",
    "TOK_DIVISION",
    "TOK_MODULO",
    "TOK_EXPONENT",

    // condition 
    "TOK_OP_EQ",
    "TOK_OP_NEQ",
    "TOK_OP_LT",
    "TOK_OP_LTE",
    "TOK_OP_GT",
    "TOK_OP_GTE",
    "TOK_OP_AND",
    "TOK_OP_OR",

    // single marks
    "TOK_OP_TENARY",
    "TOK_COMMA",
    "TOK_SEMICOLON",
    "TOK_COLON",
    "TOK_ASSIGNMENT",
    "TOK_NOT",

    // two chars
    "TOK_RARROW",

    // assignment
    "TOK_ASSIGN_PLUS",
    "TOK_ASSIGN_MINUS",
    "TOK_ASSIGN_MULTIPLY",
    "TOK_ASSIGN_DIVISION",
    "TOK_ASSIGN_MODULO",
    "TOK_ASSIGN_BITWISE_AND",
    "TOK_ASSIGN_BITWISE_OR",
    "TOK_ASSIGN_BITWISE_XOR",
    "TOK_ASSIGN_LEFT_SHIFT",
    "TOK_ASSIGN_RIGHT_SHIFT",

    // decrement and increment
    "TOK_INCREMENT",
    "TOK_DECREMENT",

    // literal
    "TOK_STRING",
    "TOK_CHAR",
    "TOK_INT",
    "TOK_FLOAT",
    "TOK_DOUBLE",

    // others
    "TOK_ERROR",
    "TOK_UNKNOWN",
    "TOK_EOF"
};

ASTNode *parseFuncDecl(Parser *p, Lexer *l) {
    ASTNode **params_node = NULL;
    ASTNode *func_decl_node = NULL;

    char *func_identifier = NULL;
    char *return_type = NULL;

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
                param_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_INT);
            break;

            case TOK_TYPE_DOUBLE:
                param_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_DOUBLE);
            break;

            case TOK_TYPE_FLOAT:
                param_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_FLOAT);
            break;

            case TOK_TYPE_CHAR:
                param_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_CHAR);
            break;

            case TOK_TYPE_STRING:
                param_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_STRING);
            break;

            case TOK_TYPE_BOOLEAN:
                param_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_BOOLEAN);
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

        createParamNode(&param_node);
        param_node->parameter.name = param_identifier;
        param_node->parameter.type = param_type;
        params_node[params_count] = param_node;
        params_count++;

        if(match(p, TOK_COMMA)) {
            eatToken(p, l, TOK_COMMA);
        }
    }

    eatToken(p, l, TOK_RPAREN);
    eatToken(p, l, TOK_RARROW);

    switch(p->current.type) {
        case TOK_TYPE_INT:
            return_type = strdup(p->current.lexeme);
            eatToken(p,l,TOK_TYPE_INT);
        break;

        case TOK_TYPE_DOUBLE:
            return_type = strdup(p->current.lexeme);
            eatToken(p,l,TOK_TYPE_DOUBLE);
        break;

        case TOK_TYPE_FLOAT:
            return_type = strdup(p->current.lexeme);
            eatToken(p,l,TOK_TYPE_FLOAT);
        break;

        case TOK_TYPE_CHAR:
                return_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_CHAR);
        break;

        case TOK_TYPE_STRING:
            return_type = strdup(p->current.lexeme);
            eatToken(p,l,TOK_TYPE_STRING);
        break;

        case TOK_TYPE_BOOLEAN:
            return_type = strdup(p->current.lexeme);
            eatToken(p,l,TOK_TYPE_BOOLEAN);
        break;

        case TOK_TYPE_VOID:
            return_type = strdup(p->current.lexeme);
            eatToken(p,l,TOK_TYPE_VOID);
        break;
    }

    eatToken(p, l, TOK_LBRACE);

    createFuncDeclNode(&func_decl_node);

    func_decl_node->function_delcaration.identifier = func_identifier;
    func_decl_node->function_delcaration.return_type = return_type;
    func_decl_node->function_delcaration.param_count = params_count;
    func_decl_node->function_delcaration.parameters = params_node;

    func_decl_node->function_delcaration.body = parseBlock(p, l);

    return func_decl_node;
}

ASTNode *parseBlock(Parser *p, Lexer *l) {
    int statements_count = 0;
    int statements_capacity = 4;
    
    ASTNode *block_node = NULL;
    
    createBlockNode(&block_node);

    block_node->block_statement.statements_count = statements_count;

    block_node->block_statement.statements = (ASTNode**)malloc(sizeof(ASTNode*) * statements_capacity);

    while(p->current.type != TOK_RBRACE && p->current.type != TOK_EOF) {
        ASTNode *statement_node = NULL;

        printf("DEBUG parseBlock: current token = %s (lexeme: %s)\n", 
           TokenTypeString[p->current.type], p->current.lexeme);
        
        switch(p->current.type) {
            case TOK_IDENTIFIER:
                if(p->next.type == TOK_LPAREN) {
                    statement_node = parseFunctionCall(p,l);
                    eatToken(p,l,TOK_SEMICOLON);
                }else if(
                    p->next.type == TOK_ASSIGNMENT ||
                    p->next.type == TOK_ASSIGN_PLUS ||
                    p->next.type == TOK_ASSIGN_MINUS ||
                    p->next.type == TOK_ASSIGN_MULTIPLY ||
                    p->next.type == TOK_ASSIGN_DIVISION
                ) {
                    statement_node = parseAssignment(p,l);
                    eatToken(p,l,TOK_SEMICOLON);
                }
            break;

            case TOK_KEY_VAR:
            case TOK_KEY_CONST:
                statement_node = parseVarDecl(p,l);
            break;

            case TOK_KEY_IF:
                statement_node = parseIf(p,l);
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

    bool is_const;

    if(match(p, TOK_KEY_VAR)) {
        eatToken(p,l,TOK_KEY_VAR);
        is_const = false;
    }else if(match(p, TOK_KEY_CONST)) {
        eatToken(p,l,TOK_KEY_CONST);
        is_const = true;
    }
    
    if(match(p, TOK_IDENTIFIER)) {
        var_identifier = strdup(p->current.lexeme);
    }

    eatToken(p,l,TOK_IDENTIFIER);
    eatToken(p,l,TOK_COLON);

    switch(p->current.type) {
        case TOK_TYPE_INT:
            if(p->next.type == TOK_LBRACKETS && p->nextNext.type == TOK_RBRACKETS) {
                eatToken(p,l,TOK_TYPE_INT);
                var_type = strdup("array int");
                eatToken(p,l,TOK_LBRACKETS);
                eatToken(p,l,TOK_RBRACKETS);
            }else {
                var_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_INT);
            }
        break;

        case TOK_TYPE_DOUBLE:
            if(p->next.type == TOK_LBRACKETS && p->nextNext.type == TOK_RBRACKETS) {
                eatToken(p,l,TOK_TYPE_DOUBLE);
                var_type = strdup("array double");
                eatToken(p,l,TOK_LBRACKETS);
                eatToken(p,l,TOK_RBRACKETS);
            }else {
                var_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_DOUBLE);
            }
        break;

        case TOK_TYPE_FLOAT:
            if(p->next.type == TOK_LBRACKETS && p->nextNext.type == TOK_RBRACKETS) {
                eatToken(p,l,TOK_TYPE_FLOAT);
                var_type = strdup("array float");
                eatToken(p,l,TOK_LBRACKETS);
                eatToken(p,l,TOK_RBRACKETS);
            }else {
                var_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_FLOAT);
            }
        break;

        case TOK_TYPE_CHAR:
            if(p->next.type == TOK_LBRACKETS && p->nextNext.type == TOK_RBRACKETS) {
                eatToken(p,l,TOK_TYPE_CHAR);
                var_type = strdup("array char");
                eatToken(p,l,TOK_LBRACKETS);
                eatToken(p,l,TOK_RBRACKETS);
            }else {
                var_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_CHAR);
            }
        break;

        case TOK_TYPE_STRING:
            if(p->next.type == TOK_LBRACKETS && p->nextNext.type == TOK_RBRACKETS) {
                eatToken(p,l,TOK_TYPE_STRING);
                var_type = strdup("array string");
                eatToken(p,l,TOK_LBRACKETS);
                eatToken(p,l,TOK_RBRACKETS);
            }else {
                var_type = strdup(p->current.lexeme);
                eatToken(p,l,TOK_TYPE_STRING);
            }
        break;

        case TOK_TYPE_BOOLEAN:
            var_type = strdup(p->current.lexeme);
            eatToken(p,l,TOK_TYPE_BOOLEAN);
        break;
    }

    createVarDeclNode(&var_decl_node);

    var_decl_node->variable_declaration.identifier = var_identifier;
    var_decl_node->variable_declaration.type = var_type;
    var_decl_node->variable_declaration.is_const = is_const;

    switch(p->current.type) {
        case TOK_SEMICOLON:
            eatToken(p,l,TOK_SEMICOLON);
        
            var_decl_node->variable_declaration.init = NULL;

            return var_decl_node;
        break;

        case TOK_ASSIGNMENT:
            if(p->next.type == TOK_LBRACE) {
                eatToken(p,l,TOK_ASSIGNMENT);
                var_decl_node->variable_declaration.init = parseArray(p,l);
                eatToken(p,l,TOK_SEMICOLON);
                return var_decl_node;
            }else {
                eatToken(p,l,TOK_ASSIGNMENT);
                var_decl_node->variable_declaration.init = parseExpression(p,l,PREC_NONE);
                eatToken(p,l,TOK_SEMICOLON);
                return var_decl_node;
            }
        break;
    }
}

ASTNode *parseIf(Parser *p, Lexer *l) {
    ASTNode *if_node = NULL;

    eatToken(p,l,TOK_KEY_IF);

    createIfNode(&if_node);

    eatToken(p,l,TOK_LPAREN);

    if_node->if_statement.condition = parseExpression(p,l,PREC_NONE);

    eatToken(p,l,TOK_RPAREN);
    eatToken(p, l, TOK_LBRACE);

    if_node->if_statement.than_branch = parseBlock(p,l);

    if(match(p,TOK_KEY_ELSE)) {
        eatToken(p,l,TOK_KEY_ELSE);
        eatToken(p,l,TOK_LBRACE);

        if_node->if_statement.else_branch = parseBlock(p,l);
    }

    return if_node;
}

ASTNode *parseWhile(Parser *p, Lexer *l);
ASTNode *parseFor(Parser *p, Lexer *l);
ASTNode *parseSwitch(Parser *p, Lexer *l);

ASTNode *parseReturn(Parser *p, Lexer *l) {
    ASTNode *return_node = NULL;

    createReturnNode(&return_node);

    eatToken(p,l,TOK_KEY_RETURN);

    if(match(p,TOK_SEMICOLON)) {
        eatToken(p,l,TOK_SEMICOLON);
        return return_node;
    }
    
    return_node->return_function.expression = parseExpression(p,l,PREC_NONE);

    eatToken(p,l,TOK_SEMICOLON);

    return return_node;
}