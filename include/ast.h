#pragma once 

typedef enum {
    NODE_ROOT,
    NODE_PROGRAM,
    NODE_FUNCTION,
    NODE_BLOCK,
    NODE_STATEMENT,
    NODE_EXPRESSION,
}NodeType;

typedef struct ASTNode ASTNode;

typedef struct {
    struct ASTNode **children;
    int child_count;
}ProgramNode;

typedef struct {
    struct ASTNode **children;
    char *return_type;
    char *identifier;
    int child_count;
}FunctionNode;

typedef struct {
    struct ASTNode **children;
    int child_count;
}BlockNode;

typedef struct {
    struct ASTNode *child;
}StatementNode;

typedef union {
    char *value_char;
    int value_int;
}ExpressionNode;

struct ASTNode {
    NodeType type;
    struct ASTNode **children;
    int child_count;
    union{
        ProgramNode program;
        FunctionNode function;
        BlockNode block;
        StatementNode statement;
        ExpressionNode expression;
    };
};

ASTNode *create_root_node(void);
ASTNode *create_program_node(ASTNode *root_node);
ASTNode *create_function_node(ASTNode *program_node, char *identifier, char *return_type);
ASTNode *create_block_node(ASTNode *function_node);
ASTNode *create_statement_node(ASTNode *block_node);
ASTNode *create_expression_node(ASTNode *statement_node, int value);

void free_ast(ASTNode *root_node, 
    ASTNode *program_node, 
    ASTNode *function_node, 
    ASTNode *block_node, 
    ASTNode *statement_node,
    ASTNode *expression_node
);
void print_ast(ASTNode *node, int indent);