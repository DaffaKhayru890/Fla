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
        FunctionCall function_call;
        Array array;
        Assignment assignment;
    };
};

void createProgramNode(ASTNode **handle_node);
void createModuleNode(ASTNode **handle_node);

void createParamNode(ASTNode **handle_node);

void createFuncDeclNode(ASTNode **handle_node);
void createReturnNode(ASTNode **handle_node);
void createBlockNode(ASTNode **handle_node);
void createVarDeclNode(ASTNode **handle_node);
void createIfNode(ASTNode **handle_node);
void createWhileNode(ASTNode **handle_node);
void createForNode(ASTNode **handle_node);
void createBreakNode(ASTNode **handle_node);
void createContinueNode(ASTNode **handle_node);
void createSwitchNode(ASTNode **handle_node);

void createBinaryNode(ASTNode **handle_node);
void createUnaryNode(ASTNode **handle_node);
void createTenaryNode(ASTNode **handle_node);
void createIdentifierNode(ASTNode **handle_node);
void createFunctionCallNode(ASTNode **handle_node);
void createLiteralNode(ASTNode **handle_node);
void createArrayNode(ASTNode **handle_node);
void createAssignmentNode(ASTNode **handle_node);

void freeAstNode(ASTNode *node, bool freeSelf);

#endif