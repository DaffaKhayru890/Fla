#ifndef FLA_AST_H
#define FLA_AST_H

typedef struct ASTNode ASTNode;

// ================================ Define enum for type ================================

typedef enum {
    NODE_PROGRAM,
    NODE_MODULE,

    NODE_FUNCTION_DECLARATION,
    NODE_VARIABLE_DECLARATION,
    NODE_IF_STATEMENT,
    NODE_WHILE_STATEMENT,
    NODE_FOR_STATEMENT,
    NODE_SWITCH_STATEMENT,

    NODE_BINARY_EXPRESSION,
    NODE_UNARY_EXPRESSION,
    // NODE_TERNARY_EXPRESSION,
    NODE_LITERAL_EXPRESSION,
    NODE_CALL_EXPRESSION,
}NodeType;

typedef enum {
    LITERAL_INT,
    LITERAL_DOUBLE,
    LITERAL_CHAR,
    LITERAL_STRING,
    LITERAL_BOOLEAN
}LiteralType;

typedef struct {
    LiteralType type;

    union {
        int int_value;
        
    };
}Literal;

typedef struct {
    char *identifier;
    char *return_type;
}FunctionDeclaration;

typedef struct {
    char *identifier;
    char *type;
}VariableDeclaration;

typedef struct {
    int elseif_count;
}If;

typedef struct {
    
}While;

typedef struct {
    
}For;

typedef struct {
    int case_count;
    
}Switch;

typedef struct {
    char *name;
}Module;

typedef struct {
    NodeType type;
    
    ASTNode *sibling;
    ASTNode *child;

    union{
        Module module;
        FunctionDeclaration function_delcaration;
        VariableDeclaration variable_declaration;
        If if_statement;
        While while_statement;
        For for_statement;
        Switch switch_statement;
    };
}ASTNode;

// =========================== Helper function ===========================

ASTNode *createNode(NodeType type);

// =========================== Create parent node ===========================

ASTNode *createProgramNode();
ASTNode *createModuleNode(char *name);

// =========================== Create function for statement node ===========================

ASTNode *createFunctionDeclarationNode(char *identifier ,char *return_type);
ASTNode *createVariableDeclarationNode(char *identifier ,char *variable_type);
ASTNode *createIfNode(int elseif_count);
ASTNode *createWhileNode();
ASTNode *createForNode();
ASTNode *createSwitchNode(int case_count);


// =========================== Create function for expression node ===========================

ASTNode *createLiteralNode(int int_value);

// =========================== Free node function ===========================

void free_node(ASTNode *node);

#endif