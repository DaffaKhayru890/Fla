#ifndef FLA_AST_H
#define FLA_AST_H

#include "../../include/node.h"
#include "../../include/literal.h"
#include "../../include/statements.h"
#include "../../include/expressions.h"

typedef struct {
    char *name;
    ASTNode *body;
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

ASTNode *createFuncDeclNode(ASTNode **handle, char *identifier, char *return_type, char* function_name);
ASTNode *createReturnNode(ASTNode **handle);
ASTNode *createBlockNode(ASTNode **handle);
ASTNode *createVarDeclNode(ASTNode **handle, char *identifier, char *type);
ASTNode *createIfNode(ASTNode **handle, int elseif_count);
ASTNode *createWhileNode(ASTNode **handle);
ASTNode *createForNode(ASTNode **handle);
ASTNode *createBreakNode(ASTNode **handle);
ASTNode *createContinueNode(ASTNode **handle);
ASTNode *createSwitchNode(ASTNode **handle, int case_count);



#endif