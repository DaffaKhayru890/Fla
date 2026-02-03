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
};

ASTNode *createProgramNode(ASTNode **handle);
ASTNode *createModuleNode(ASTNode **handle, char *name);

ASTNode *createFuncDeclNode(ASTNode **handle, char *identifier, char *return_type, int arg_count, int capacity);
ASTNode *createReturnNode(ASTNode **handle);
ASTNode *createBlockNode(ASTNode **handle);
ASTNode *createVarDeclNode(ASTNode **handle, char *identifier, char *type);
ASTNode *createIfNode(ASTNode **handle, int elseif_count);
ASTNode *createWhileNode(ASTNode **handle);
ASTNode *createForNode(ASTNode **handle);
ASTNode *createBreakNode(ASTNode **handle);
ASTNode *createContinueNode(ASTNode **handle);
ASTNode *createSwitchNode(ASTNode **handle, int case_count);



void freeAstNode(ASTNode *node, bool freeSelf);

#endif