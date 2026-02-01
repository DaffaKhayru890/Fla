#pragma once 

#include "stdbool.h"

typedef struct ASTNode ASTNode;

typedef enum {
    NODE_PROGRAM,       
    NODE_MODULE,        
    NODE_STATEMENT,     
    NODE_EXPRESSION
}NodeType;

typedef enum {
    EXPRESSION_BINARY,
    EXPRESSION_FUNCTION_CALL,
}ExpressionKind;

typedef enum {
    LITERAL_STRING,
    LITERAL_CHAR,
    LITERAL_DOUBLE,
    LITERAL_INT,
    LITERAL_BOOLEAN,
}LiteralKind;

typedef enum {
    // UNARY_NEGATE,      // -
    // UNARY_NOT,         // !
    UNARY_PRE_INCREMENT,     // ++x
    UNARY_POST_INCREMENT,    // x++
    UNARY_PRE_DECREMENT,     // --x
    UNARY_POST_DECREMENT,    // x--
    // UNARY_BITWISE_NOT, // ~
    // UNARY_ADDRESS_OF,  // &
    // UNARY_DEREFERENCE, // *
}UnaryOperator;

typedef enum {
    ASSIGN_EQUAL,     // =
    ASSIGN_PLUS,        // +=
    ASSIGN_MINUS,        // -=
    ASSIGN_MULTIPLY,        // *=
    ASSIGN_DIVISION,        // /=
    ASSIGN_MODULO,        // %=
    ASSIGN_BITWISE_AND,// &=
    ASSIGN_BITWISE_OR, // |=
    ASSIGN_BITWISE_XOR,// ^=
}AssignOperator;

typedef enum {
    STATEMENT_BLOCK,
    STATEMENT_FUNCTION_DECLARATION,
    STATEMENT_VARIABLE_DECLARATION,
    STATEMENT_IF,
    STATEMENT_WHILE,
    STATEMENT_FOR,
    STATEMENT_SWITCH,
    STATEMENT_RETURN,
    STATEMENT_BREAK,
    STATEMENT_CONTINUE,
    STATEMENT_EXPRESSION,
}StatementKind;

typedef enum {
    RETURN_STRING,
    RETURN_INT,
    RETURN_CHAR,
    RETURN_DOUBLE,
    RETURN_BOOLEAN,
}ReturnType;

typedef struct {
    ExpressionKind expression_kind;
    union {
        struct {
            char *operator;
            // children left, right
        }Binary;

        struct {
            int argument_count;
            // children arguments
        }FunctionCall;

        struct {
            UnaryOperator operator;
            // child operand
            bool is_postfix; 
        }Unary;

        struct {
            AssignOperator operator;
            // children left, righ
        }Assignment;

        struct {
            int parameter_count;
            char *name;
            char *type;
            // children parameter
        }Parameter;

        struct {
            LiteralKind literal_kind;
            union {
                char *string_value;
                int int_value;
                char char_value;
                int boolean_value;
                double double_value;
            };
        }Literal;
    };
}Expression;

typedef struct {
    StatementKind statement_kind;
    union {
        struct {
            
        }Block;

        struct {
            char *name;
            char *return_type;
            int param_count;
            // child block
        }FunctionDeclaration;

        struct {
            char *name;
            char *type;
            // child initializer
        }VariableDeclaration;

        struct {
            ReturnType return_type;
        }Return;

        struct {
            int elseif_count;
            // children condition, elseif_branch
        }If;

        struct {
            // children condition, block
        }While;

        struct {
            // children initialization, conditional, unary
        }For;

        struct {
            int case_count;
            // children expression, block
        }Switch; 
    };
}Statement;

typedef struct {
    char *name;
}Module;

struct ASTNode {
    NodeType type;
    
    ASTNode **children;

    int child_count;

    union{
        Module module;
        Statement statement;
        Expression expression;
    };
};

ASTNode *create_node(NodeType node_type);
ASTNode *create_program_node();
ASTNode *create_module_node(char *name);

ASTNode *create_function_declaration_node(char *name, char *return_type);
ASTNode *create_return_node(char *name, char *return_type);
ASTNode *create_block_node();
ASTNode *create_variable_declaration_node(char *name, char *type);
ASTNode *create_if_node(int else_count);
ASTNode *create_while_node();
ASTNode *create_for_node();
ASTNode *create_switch_node(int case_count);

ASTNode *create_binary_expression_node();
ASTNode *create_function_call_node(int argument_count);
ASTNode *create_literal_node(LiteralKind literal_kind, int int_value, double double_value, char char_value, char *string_value, bool bool_value);
ASTNode *create_unary_node(UnaryOperator unary_operator ,bool is_postfix);
ASTNode *create_assignment_node(AssignOperator assign_operator);
ASTNode *create_paremeter_node(char *param_name, char *param_type);

void add_child_to_parent_children(ASTNode *parent, ASTNode* child);

void free_node(ASTNode *node);
void free_statement(ASTNode *node);
void free_expression(ASTNode *node);