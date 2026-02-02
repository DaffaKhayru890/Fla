#ifndef FLA_AST_H
#define FLA_AST_H

typedef struct ASTNode ASTNode;

// ================================ Define enum for type ================================

typedef enum {
    NODE_PROGRAM,
    NODE_MODULE,
    NODE_STATEMENT,
    NODE_EXPRESSION
}NodeType;

typedef enum {
    STATEMENT_FUNCTION_DECLARATION,
    STATEMENT_VARIABLE_DECLARATION,
    STATEMENT_IF,
    STATEMENT_WHILE,
    STATEMENT_FOR,
    STATEMENT_SWITCH,
}StatementType;

typedef enum {
    EXPRESSION_BINARY,
    EXPRESSION_UNARY,
    EXPRESSION_LITERAL,
    EXPRESSION_TENARY,
    EXPRESSION_CALL,
    EXPRESSION_MEMBER,
    EXPRESSION_ASSIGNMENT,
    EXPRESSION_CAST,
}ExpressionType;

typedef enum {
    LITERAL_INT,
    LITERAL_DOUBLE,
    LITERAL_CHAR,
    LITERAL_STRING,
    LITERAL_BOOLEAN
}LiteralType;

// ================================ Define statement node ================================

typedef struct {
    char *identifier;
    char *return_type;
    ASTNode **body;
}FunctionDeclaration;

typedef struct {
    char *identifier;
    char *type;
    ASTNode *init;
}VariableDeclaration;

typedef struct {
    int elseif_count;
    ASTNode *condition;
    ASTNode **than_branch;
    ASTNode **else_branch;
}If;

typedef struct {
    ASTNode *condition;
    ASTNode **body;
    int body_count;
}While;

typedef struct {
    ASTNode *init;
    ASTNode *condition;
    ASTNode *postfix;
    ASTNode **body;
}For;

typedef struct {
    int case_count;
    ASTNode *expression;
    ASTNode **body;
}Switch;

// ================================ Define expression node ================================

typedef struct {
    LiteralType type;
    union {
        int int_value;
        double double_value;
        char char_value;
        char *string_value;
        bool boolean_value;
    };
}Literal;

// ================================ Define main node ================================

typedef struct {
    NodeType type;
    ASTNode **children;
    int child_count;

    union{
        FunctionDeclaration function_delcaration;
        VariableDeclaration variable_declaration;
        If if_statement;
        While while_statement;
        For for_statement;
        Switch switch_statement;

    };
}ASTNode;

// =========================== Create function for statement node ===========================

ASTNode *createFunctionDeclarationNode(ASTNode **body , char *identifier ,char *return_type);
ASTNode *createVariableDeclarationNode(ASTNode **body, char *identifier ,char *variable_type);
ASTNode *createIfNode(ASTNode *condition, ASTNode **than_branch, ASTNode **else_branch);
ASTNode *createWhileNode(ASTNode *contidion, ASTNode **body);
ASTNode *createForNode(ASTNode *init, ASTNode *condition, ASTNode *postfix, ASTNode**body);
ASTNode *createSwitchNode(ASTNode *expression, ASTNode **body);


// =========================== Create function for expression node ===========================


// =========================== Free node function ===========================

void free_node(ASTNode *node);
void free_statement(ASTNode *node);
void free_expression(ASTNode *node);

#endif