#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_binary_node(char *operator) {
    ASTNode *binary_expression = create_node(NODE_EXPRESSION);

    binary_expression->expression.expression_kind = EXPRESSION_BINARY;
    binary_expression->children = NULL;
    binary_expression->child_count = 0;
    binary_expression->expression.Binary.operator = strdup(operator);

    return binary_expression;
}

ASTNode *create_function_call_node(int argument_count) {
    ASTNode *function_call = create_node(NODE_EXPRESSION);

    function_call->expression.expression_kind = EXPRESSION_FUNCTION_CALL;
    function_call->children = NULL;
    function_call->child_count = 0;
    function_call->expression.FunctionCall.argument_count = argument_count;

    return function_call;
}

ASTNode *create_literal_node(LiteralKind literal_kind, int int_value, double double_value, char char_value, char *string_value, bool bool_value) {
    ASTNode *literal = create_node(NODE_EXPRESSION);

    literal->expression.Literal.literal_kind = literal_kind;

    switch(literal_kind) {
        case LITERAL_INT:
            literal->expression.Literal.int_value = int_value;
        break;

        case LITERAL_DOUBLE:
            literal->expression.Literal.double_value = double_value;
        break;

        case LITERAL_CHAR:
            literal->expression.Literal.char_value = char_value;
        break;

        case LITERAL_STRING:
            literal->expression.Literal.string_value = string_value;
        break;

        case LITERAL_BOOLEAN:
            literal->expression.Literal.boolean_value = bool_value;
        break;
    }

    return literal;
}

ASTNode *create_unary_node(UnaryOperator unary_operator, bool is_postfix) {
     ASTNode *unary = create_node(NODE_EXPRESSION);

    unary->expression.Unary.operator = unary_operator;
    unary->children = NULL;
    unary->child_count = 0;
    unary->expression.Unary.is_postfix = is_postfix;

    return unary;
}

ASTNode *create_assignment_node(AssignOperator assignment_operator) {
    ASTNode *assignment = create_node(NODE_EXPRESSION);

    assignment->expression.Assignment.operator = assignment_operator;
    assignment->children = NULL;
    assignment->child_count = 0;

    return assignment;
}

ASTNode *create_paremeter_node(char *param_name, char *param_type) {
    ASTNode *parameter = create_node(NODE_EXPRESSION);

    parameter->expression.Parameter.name = strdup(param_name);
    parameter->expression.Parameter.type = strdup(param_type);
    parameter->children = NULL;
    parameter->child_count = 0;

    return parameter;
}