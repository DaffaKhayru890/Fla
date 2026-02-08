#include "../../include/parser.h"
#include "../../include/memory.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

ASTNode *parseAtom(Parser *p, Lexer *l) {
    ASTNode *atom = NULL;
    
    switch(p->current.type) {
        case TOK_INT:
        case TOK_DOUBLE:
        case TOK_FLOAT:
        case TOK_CHAR:
        case TOK_STRING:
        case TOK_KEY_TRUE:
        case TOK_KEY_FALSE:
            atom = parseLiteral(p,l);
        break;

        case TOK_LPAREN:
            eatToken(p,l,TOK_LPAREN);
            atom = parseExpression(p,l,PREC_NONE);
            eatToken(p,l,TOK_RPAREN);
        break;

        case TOK_IDENTIFIER:
            if(p->next.type == TOK_LPAREN) {
                atom = parseFunctionCall(p,l);
            }else {
                char *identifier = strdup((void *)p->current.lexeme);
                atom = parseIdentifier(p,l,identifier);
                free(identifier);
            }
        break;
    }

    return atom;
}

ASTNode *parseInfix(Parser *p, Lexer *l, ASTNode *left) {
    char *op = strdup(p->current.lexeme);

    Precedence prec = getPrecedence(p->current.type);

    eatToken(p,l,p->current.type);

    ASTNode *right = parseExpression(p,l,prec);

    ASTNode *binary = NULL;

    createBinaryNode(&binary);
    binary->binary.op = op;

    binary->binary.right = right;
    binary->binary.left = left;

    return binary;
}

ASTNode *parsePrefix(Parser *p, Lexer *l) {
    switch(p->current.type) {
        case TOK_INCREMENT:
        case TOK_DECREMENT:
        case TOK_MINUS:
        case TOK_NOT: {
            char *op = strdup(p->current.lexeme);

            eatToken(p,l,p->current.type);

            Precedence prec = getPrecedence(p->current.type);

            ASTNode *operand = parseExpression(p,l,prec);

            ASTNode *unary = NULL;

            createUnaryNode(&unary);
            unary->unary.op = op;


            unary->unary.operand = operand;
            unary->unary.is_postfix = false;

            free(op);

            return unary;
        }

        default:
            return parseAtom(p,l);
    }
}

ASTNode *parsePostfix(Parser *p, Lexer *l, ASTNode *left) {
    switch(p->current.type) {
        case TOK_INCREMENT:
        case TOK_DECREMENT: {
            char *op = strdup(p->current.lexeme);

            eatToken(p,l,p->current.type);

            ASTNode *unary = NULL;

            createUnaryNode(&unary);
            unary->unary.op = op;

            unary->unary.operand = left;
            unary->unary.is_postfix = true;

            free(op);

            return unary;
        }
    }
}

ASTNode *parseExpression(Parser *p, Lexer *l, Precedence min_precedence) {
    ASTNode *left = parsePrefix(p,l);

    if(!left) return NULL;

    while(min_precedence < getPrecedence(p->current.type)) {
        switch(p->current.type) {
            case TOK_INCREMENT:
            case TOK_DECREMENT: {
                left = parsePostfix(p,l,left);
                break;
            }

            default:
                left = parseInfix(p,l,left);
        }   
    }

    return left;
}

ASTNode *parseFunctionCall(Parser *p, Lexer *l) {
    int args_count = 0;
    int args_capacity = 4;
    char *function_call_name = NULL;

    ASTNode *function_call_node = NULL;

    if(match(p, TOK_IDENTIFIER)) {
        function_call_name = strdup(p->current.lexeme);
    }

    eatToken(p,l,TOK_IDENTIFIER);

    createFunctionCallNode(&function_call_node);

    function_call_node->function_call.arg_count = args_count;

    eatToken(p,l,TOK_LPAREN);

    function_call_node->function_call.function_name = function_call_name;
    function_call_node->function_call.arguments = (ASTNode**)malloc(sizeof(ASTNode*) * args_capacity);

    while(p->current.type != TOK_RPAREN && p->current.type != TOK_EOF) {
        ASTNode *literal_node = NULL;

        switch(p->current.type) {
            case TOK_INT:
            case TOK_DOUBLE:
            case TOK_FLOAT:
            case TOK_CHAR:
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

    free(function_call_name);

    eatToken(p,l,TOK_RPAREN);

    return function_call_node;
}

ASTNode *parseIdentifier(Parser *p, Lexer *l, void *identifier) {
    ASTNode *identifier_node = NULL;
    char *identifier_name = NULL;

    if(identifier != NULL) {
        identifier_name = strdup((char*)identifier);
    }else if(match(p, TOK_IDENTIFIER)) {
        identifier_name = strdup(p->current.lexeme);
    }

    eatToken(p,l, TOK_IDENTIFIER);

    createIdentifierNode(&identifier_node);
    identifier_node->identifier.identifier = identifier_name;

    return identifier_node;
}

ASTNode *parseLiteral(Parser *p, Lexer *l) {
    ASTNode *literal_node = NULL;

    switch(p->current.type) {
        case TOK_INT: {
            int *int_value = (int*)malloc(sizeof(int));
            *int_value = atoi(p->current.lexeme);
            createLiteralNode(&literal_node);
            literal_node->literal.literal_type = LITERAL_INT;
            literal_node->literal.int_value = int_value;
            eatToken(p,l,TOK_INT);
            break;
        }

        case TOK_DOUBLE: {
            double *double_value = (double*)malloc(sizeof(double));
            *double_value = atof(p->current.lexeme);
            createLiteralNode(&literal_node);
            literal_node->literal.literal_type = LITERAL_DOUBLE;
            literal_node->literal.double_value = double_value;
            eatToken(p,l,TOK_DOUBLE);
            break;
        }

        case TOK_FLOAT: {
            float *float_value = (float*)malloc(sizeof(float));
            *float_value = (float)atof(p->current.lexeme);
            createLiteralNode(&literal_node);
            literal_node->literal.literal_type = LITERAL_FLOAT;
            literal_node->literal.float_value = float_value;
            eatToken(p,l,TOK_FLOAT);
            break;
        }
            
        case TOK_CHAR: {
            char *char_value = (char*)malloc(sizeof(char));
            *char_value = p->current.lexeme[0];
            createLiteralNode(&literal_node);
            literal_node->literal.literal_type = LITERAL_CHAR;
            literal_node->literal.char_value = char_value;
            eatToken(p,l,TOK_CHAR);
            break;
        }     

        case TOK_STRING: {
            char *string_value = strdup(p->current.lexeme);
            createLiteralNode(&literal_node);
            literal_node->literal.literal_type = LITERAL_STRING;
            literal_node->literal.string_value = string_value;
            eatToken(p,l,TOK_STRING);
            break;
        }

        case TOK_KEY_TRUE:
        case TOK_KEY_FALSE: {
            createLiteralNode(&literal_node);
            literal_node->literal.literal_type = LITERAL_BOOLEAN;
            literal_node->literal.boolean_value = (p->current.type == TOK_KEY_TRUE);
            
            if(match(p, TOK_KEY_TRUE)) {
                eatToken(p,l,TOK_KEY_TRUE);
            }else {
                eatToken(p,l,TOK_KEY_FALSE);
            }
            
            break;
        }
    }

    return literal_node;
}

ASTNode *parseArray(Parser *p, Lexer *l) {
    ASTNode *array = NULL;

    int literals_count = 0;
    int literals_capacity = 4;
    
    eatToken(p,l, TOK_LBRACE);

    createArrayNode(&array);

    array->array.literal_count = literals_count;

    array->array.literal = (ASTNode**)malloc(sizeof(ASTNode*) * literals_capacity);

    while(p->current.type != TOK_RBRACE) {
        if(match(p,TOK_COMMA)) {
            eatToken(p,l, TOK_COMMA);
            continue;
        }

        switch(p->current.type) {
            case TOK_INT:
            case TOK_DOUBLE:
            case TOK_FLOAT:
            case TOK_CHAR:
            case TOK_STRING:
            case TOK_KEY_TRUE:
            case TOK_KEY_FALSE:
                array->array.literal[literals_count] = parseLiteral(p,l);
                literals_count++;
            break;
        }

        if(literals_count >= literals_capacity) {
            literals_capacity = literals_capacity * 2;
            array->array.literal = (ASTNode**)realloc(
                array->array.literal,
                sizeof(ASTNode*) * literals_capacity
            );
        }
    }

    array->array.literal[literals_count] = NULL;
    array->array.literal_count = literals_count;

    eatToken(p,l,TOK_RBRACE);

    return array;
}

ASTNode *parseAssignment(Parser *p, Lexer *l) {
    ASTNode *assignment = NULL;
    ASTNode *identifier = NULL;

    char *identifier_name = strdup(p->current.lexeme);

    createAssignmentNode(&assignment);
    createIdentifierNode(&identifier);

    identifier->identifier.identifier = identifier_name;

    eatToken(p,l,TOK_IDENTIFIER);
    
    switch(p->current.type) {
        case TOK_ASSIGNMENT: {
            char *left = strdup(p->current.lexeme);
            assignment->assignment.left = left;
            eatToken(p,l,TOK_ASSIGNMENT);
            break;
        }    

        case TOK_ASSIGN_PLUS: {
            char *left = strdup(p->current.lexeme);
            assignment->assignment.left = left;
            eatToken(p,l,TOK_ASSIGN_PLUS);
            break;
        }
            
        case TOK_ASSIGN_MINUS: {
            char *left = strdup(p->current.lexeme);
            assignment->assignment.left = left;
            eatToken(p,l,TOK_ASSIGN_MINUS);
            break;
        }
            
        case TOK_ASSIGN_MULTIPLY: {
            char *left = strdup(p->current.lexeme);
            assignment->assignment.left = left;
            eatToken(p,l,TOK_ASSIGN_MULTIPLY);
            break;
        }  

        case TOK_ASSIGN_DIVISION: {
            char *left = strdup(p->current.lexeme);
            assignment->assignment.left = left;
            eatToken(p,l,TOK_ASSIGN_DIVISION);
            break;
        }
            
    }

    assignment->assignment.expression = parseExpression(p,l,PREC_NONE);

    return assignment;
}