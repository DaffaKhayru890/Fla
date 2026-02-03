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
    NODE_TERNARY_EXPRESSION,
    NODE_COMPOUND_EXPRESSION,
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

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_BOOLEAN
}DataType;

// ================================ Define statement ================================

typedef struct {
    union {
        int int_value;
        double double_value;
        char char_value;
        char *string_value;
        bool bool_value;
    };
}Literal;

typedef struct {
    char *name;
}Identifier;

typedef struct {
    char *op;
    ASTNode *left;
    ASTNode *right;
}Binary;

typedef struct {
    char *op;
    ASTNode *operand;
}Unary;

typedef struct {
    ASTNode *condition;
    ASTNode *then_expr;
    ASTNode *else_expr;
}Ternary;

typedef struct {
    ASTNode *expression;
}Grouping;

typedef struct {    
    int count;
    int capacity;
}Compound;

// ================================ Define statement ================================

typedef struct {
    char *identifier;
    char *return_type;
    char* function_name;
    ASTNode* arguments;    
    int arg_count;
    int arg_capacity;
}FunctionDeclaration;

typedef struct {
    ASTNode* return_value;
}Return;

typedef struct {
    ASTNode *statements;
    int count;
    int capacity;
}Block;

typedef struct {
    char *identifier;
    char *type;
}VariableDeclaration;

typedef struct {
    int elseif_count;
    ASTNode* condition;     
    ASTNode* then_branch;   
    ASTNode* else_branch;   
}If;

typedef struct {
    ASTNode* condition;   
    ASTNode* body;  
}While;

typedef struct {
    ASTNode* initializer;   
    ASTNode* condition;     
    ASTNode* increment;     
    ASTNode* body;          
}For;

typedef struct {
    
}Break;

typedef struct {
    
}Continue;

typedef struct {
    int case_count;
    
}Switch;

typedef struct {
    char *name;
}Module;

typedef struct {
    NodeType node_type;
    LiteralType literal_type;
    DataType data_type;

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