#pragma once 

typedef enum {
    NODE_ROOT,
    NODE_MODULE,
    NODE_FUNCTION_DECLARATION,
    NODE_BLOCK,
    NODE_FUNCTION_CALL,
    NODE_ARGUMENT,
    NODE_STRING_LITERAL
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
    };
};

ASTNode *create_root_node(void);
ASTNode *create_module_node(ASTNode *root_node, char *name);
ASTNode *create_function_declaration_node(ASTNode *module_node, ASTNode *class_node, char *identifier, char *return_type);
ASTNode *create_block_node(ASTNode *function_declaration_node);
ASTNode *create_function_call_node(ASTNode *block_node, char *identifier);
ASTNode *create_argument_node(ASTNode *function_call_node);
ASTNode *create_string_literal_node(ASTNode *argument_node, char *value);

void free_node(ASTNode *node);