#include "../../include/parser.h"
#include "../../include/memory.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

ASTNode *parsePrimary(Parser *p, Lexer *l) {
    ASTNode *primary_node = NULL;

    switch(p->current.type) {
        case TOK_INT:
        case TOK_DOUBLE:
        case TOK_FLOAT:
        case TOK_CHAR:
        case TOK_STRING:
            primary_node = parseLiteral(p, l);
        break;

        case TOK_INCREMENT:
        case TOK_DECREMENT:

        break;
    }

    return primary_node;
}

ASTNode *parsePostfix(Parser *p, Lexer *l, ASTNode *left) {
    switch(p->current.type) {
        case TOK_INCREMENT:
        case TOK_DECREMENT: {
            char *op = strdup(p->current.lexeme);
            printf("hello");
            eatToken(p, l, p->current.type);

            ASTNode *postfix_node = NULL;
            createUnaryNode(&postfix_node, op);
            postfix_node->unary.operand = left;
            postfix_node->unary.is_postfix = true;

            free(op);
            return postfix_node;
        }

        default:
            return left;
    }
}

ASTNode *parseExpression(Parser *p, Lexer *l, Precedence precedence) {
    ASTNode *left = parsePrimary(p,l);

    printf("%s", p->current.lexeme);

    while(precedence < getPrecedence(p->current.type)) {
        if(p->current.type == TOK_INCREMENT || p->current.type == TOK_DECREMENT) {
            left = parsePostfix(p, l, left);
            continue;
        }

        Precedence op = getPrecedence(p->current.type);

        char *operator = strdup(p->current.lexeme);

        eatToken(p,l,p->current.type);

        ASTNode *right = parseExpression(p,l,op);

        ASTNode *binary_node = NULL;
        createBinaryNode(&binary_node, operator);

        binary_node->binary.left = left;
        binary_node->binary.right = right;

        left = binary_node;

        free(operator);
    }
    
    return left;
}

ASTNode *parserFunctionCall(Parser *p, Lexer *l) {
    int args_count = 0;
    int args_capacity = 4;
    char *function_call_name = NULL;

    ASTNode *function_call_node = NULL;

    if(match(p, TOK_IDENTIFIER)) {
        function_call_name = strdup(p->current.lexeme);
    }

    eatToken(p,l,TOK_IDENTIFIER);

    createFunctionCallNode(&function_call_node, args_count);

    eatToken(p,l,TOK_LPAREN);

    function_call_node->function_call.function_name = function_call_name;
    function_call_node->function_call.arguments = (ASTNode**)malloc(sizeof(ASTNode*) * args_capacity);

    while(p->current.type != TOK_RPAREN && p->current.type != TOK_EOF) {
        ASTNode *literal_node = NULL;

        switch(p->current.type) {
            case TOK_STRING:
                literal_node = parseLiteral(p,l);
            break;
        }

        if(args_count >= args_capacity) {
            args_capacity = args_capacity * 2;
            function_call_node->function_call.arguments = (ASTNode**)realloc(
                function_call_node->function_call.arguments,
                sizeof(ASTNode*) * args_capacity
            );
        }

    
        function_call_node->function_call.arguments[args_count] = literal_node;

        if(match(p, TOK_COMMA)) {
            eatToken(p,l,TOK_COMMA);
        }

        args_count++;
    }

    function_call_node->function_call.arguments[args_count] = NULL;
    function_call_node->function_call.arg_count = args_count;

    // free(function_call_name);

    eatToken(p,l,TOK_RPAREN);
    eatToken(p,l,TOK_SEMICOLON);

    return function_call_node;
}

ASTNode *parserVariableCall(Parser *p, Lexer *l) {
    ASTNode *variable_call_node = NULL;
    char *variable_call_identifier = NULL;

    if(match(p, TOK_IDENTIFIER)) {
        variable_call_identifier = strdup(p->current.lexeme);
    }

    eatToken(p,l, TOK_IDENTIFIER);

    createVariableCall(&variable_call_node, variable_call_identifier);

    free(variable_call_identifier);

    return variable_call_node;
}

ASTNode *parseLiteral(Parser *p, Lexer *l) {
    ASTNode *literal_node = NULL;

    switch(p->current.type) {
        case TOK_INT:
            int *int_value = (int*)malloc(sizeof(int));
            *int_value = atoi(p->current.lexeme);
            createLiteralNode(&literal_node, LITERAL_INT, int_value);
            eatToken(p,l,TOK_INT);
        break;

        case TOK_DOUBLE:
            double *double_value = (double*)malloc(sizeof(double));
            *double_value = atof(p->current.lexeme);
            createLiteralNode(&literal_node, LITERAL_DOUBLE, double_value);
            eatToken(p,l,TOK_DOUBLE);
        break;

        case TOK_FLOAT:
            float *float_value = (float*)malloc(sizeof(float));
            *float_value = (float)atof(p->current.lexeme);
            createLiteralNode(&literal_node, LITERAL_FLOAT, double_value);
            eatToken(p,l,TOK_DOUBLE);
        break;

        case TOK_CHAR:
            char *char_value = (char*)malloc(sizeof(char));
            *char_value = p->current.lexeme[0];
            createLiteralNode(&literal_node, LITERAL_CHAR, char_value);
            eatToken(p,l,TOK_CHAR);
        break;

        case TOK_STRING:
            char *string_value = strdup(p->current.lexeme);
            createLiteralNode(&literal_node, LITERAL_STRING, string_value);
            eatToken(p,l,TOK_STRING);
        break;
    }

    return literal_node;
}