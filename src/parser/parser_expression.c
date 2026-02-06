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
            primary_node = parseLiteral(p,l);
        break; 
    }

    return primary_node;
}

ASTNode *parseExpression(Parser *p, Lexer *l, Precedence precedence) {
    ASTNode *expression = parsePrimary(p,l);

    while(precedence < getPrecedence(p->current.type)) {
        Precedence op = getPrecedence(p->current.type);

        char *operator = strdup(p->current.lexeme);

        eatToken(p,l,p->current.type);

        ASTNode *right = parseExpression(p,l,op);

        ASTNode *binary_node = NULL;
        createBinaryNode(&binary_node, operator);

        binary_node->binary.left = expression;
        binary_node->binary.right = right;

        expression = binary_node;

        free(operator);
    }
    
    return expression;
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
        ASTNode *argument_node = NULL;
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

        createArgumentNode(&argument_node);
        argument_node->argument.literal = literal_node;

        function_call_node->function_call.arguments[args_count] = argument_node;

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

        case TOK_STRING:
            char *string_value = strdup(p->current.lexeme);
            createLiteralNode(&literal_node, LITERAL_STRING, string_value);
            eatToken(p,l,TOK_STRING);
        break;
    }

    return literal_node;
}