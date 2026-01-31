#pragma once 

typedef enum {
    NODE_PROGRAM,
    NODE_MODULE,
    NODE_FUNCTION_DECLARATION,
    NODE_BLOCK,
    NODE_FUNCTION_CALL,
    NODE_ARGUMENT,
    NODE_STRING_LITERAL,
    NODE_VARIABLE_DECLARATION,
    NODE_BINARY_EXPRESSION,
}NodeType;

typedef struct ASTNode ASTNode;

typedef struct {
    char *name;
}ModuleNode;

typedef struct {
    char *identifier;
    char *return_type;
}FunctionDeclarationNode;

typedef struct {
    
}BlockNode;

typedef struct {
    char *identifier;
}FunctionCallNode;

typedef struct {
    
}ArgumentNode;

typedef struct {
    char *identifier;
}VariableDeclaration;

typedef struct {

}BinaryExpression;

typedef struct {
    char *value;
}StringLiteral;

struct ASTNode {
    NodeType type;
    struct ASTNode **children;
    struct ASTNode *child;
    int child_count;
    union{
        ModuleNode module;
        FunctionDeclarationNode function_declaration;
        BlockNode block;
        FunctionCallNode function_call_node;
        ArgumentNode argument;
        StringLiteral string_literal;
        VariableDeclaration variable_declaration;
        BinaryExpression binary_expression;
    };
};

ASTNode *create_program_node();
ASTNode *create_module_node(char *name);
ASTNode *create_function_declaration_node(char *identifier, char *return_type);
ASTNode *create_block_node();
ASTNode *create_function_call_node(char *identifier);
ASTNode *create_argument_node();
ASTNode *create_string_literal_node(char *value);
ASTNode *create_variable_declaration_node(char *identifier);
ASTNode *create_binary_expression_node();

void add_child_to_parent_child(ASTNode *parent_node, ASTNode *child);
void add_child_to_parent_children(ASTNode *parent_node, ASTNode *child);

void free_ast_node(ASTNode *node);