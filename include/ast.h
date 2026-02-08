#ifndef FLA_AST_H
#define FLA_AST_H

#include "./node.h"
#include "./literal.h"
#include "./statements.h"
#include "./expressions.h"

#include <stdbool.h>

typedef struct {
    char *name;
    char *type;
}Parameter;

typedef struct {
    char *name;
    ASTNode **body;
}Module;

struct ASTNode {
    NodeType node_type;
    ASTNode *body;
    
    union {
        Module module;

        Parameter parameter;

        FunctionDeclaration function_delcaration;
        Block block_statement;
        Return return_function;
        VariableDeclaration variable_declaration;
        If if_statement;
        Break breal_statement;
        Continue continue_statement;
        While while_statement;
        For for_statement;
        Switch switch_statement;

        Literal literal;
        Identifier identifier;
        Binary binary;
        Unary unary;
        Ternary tenary;
        Grouping grouping;
        Compound compound;
        FunctionCall function_call;
        Array array;
        Assignment assignment;
    };
};

void createProgramNode(ASTNode **handle_node);
void createModuleNode(ASTNode **handle_node, char *name);

void createParamNode(ASTNode **handle_node, char *name, char *type);

void createFuncDeclNode(ASTNode **handle_node, char *identifier, char *return_type, int param_count);
void createReturnNode(ASTNode **handle_node);
void createBlockNode(ASTNode **handle_node, int statements_count);
void createVarDeclNode(ASTNode **handle_node, char *identifier, char *type, VarType variable_type);
void createIfNode(ASTNode **handle_node, int elseif_count);
void createWhileNode(ASTNode **handle_node);
void createForNode(ASTNode **handle_node);
void createBreakNode(ASTNode **handle_node);
void createContinueNode(ASTNode **handle_node);
void createSwitchNode(ASTNode **handle_node, int case_count);

void createBinaryNode(ASTNode **handle_node, char *op);
void createUnaryNode(ASTNode **handle_node, char *op);
void createTenaryNode(ASTNode **handle_node);
void createGroupingNode(ASTNode **handle_node);
void createCompoundNode(ASTNode **handle_node, int count, int capacity);
void createFunctionCallNode(ASTNode **handle_node, int arg_count);
void createLiteralNode(ASTNode **handle_node, LiteralType literal_type, void *value);
void createArrayNode(ASTNode **handle_node, int literal_count);
void createAssignmentNode(ASTNode **handle_node);
void createIdentifierNode(ASTNode **handle_node, char *identifier);

void freeAstNode(ASTNode *node, bool freeSelf);

#endif