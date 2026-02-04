#ifndef FLA_AST_H
#define FLA_AST_H

#include "./node.h"
#include "./literal.h"
#include "./statements.h"
#include "./expressions.h"

#include <stdbool.h>

typedef struct {
    NodeType node_type;
    char *name;
    ASTNode *body;
}Module;

typedef struct {
    NodeType node_type;
    ASTNode *body;
}Program;

union ASTNode {
    NodeType node_type;

    Program;
    Module module;

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
};

void createProgramNode(ASTNode **handle_node);
void createModuleNode(ASTNode **handle_node, char *name);

void createFuncDeclNode(ASTNode **handle_node, char *identifier, char *return_type, int arg_count, int capacity);
void createReturnNode(ASTNode **handle_node);
void createBlockNode(ASTNode **handle_node);
void createVarDeclNode(ASTNode **handle_node, char *identifier, char *type);
void createIfNode(ASTNode **handle_node, int elseif_count);
void createWhileNode(ASTNode **handle_node);
void createForNode(ASTNode **handle_node);
void createBreakNode(ASTNode **handle_node);
void createContinueNode(ASTNode **handle_node);
void createSwitchNode(ASTNode **handle_node, int case_count);

void createIdentifierNode(ASTNode **handle_node, char *name);
void createBinaryNode(ASTNode **handle_node, char *op);
void createUnaryNode(ASTNode **handle_node, char *op);
void createTenaryNode(ASTNode **handle_node);
void createGroupingNode(ASTNode **handle_node);
void createCompoundNode(ASTNode **handle_node, int count, int capacity);
void createFunctionCallNode(ASTNode **handle_node, char *function_name, int arg_count, int arg_capacity);
void createLiteralNode(ASTNode **handle_node, LiteralType literal_type);

void addModuleToProgram(ASTNode *parent, ASTNode *child);

void freeAstNode(ASTNode *node, bool freeSelf);

#endif