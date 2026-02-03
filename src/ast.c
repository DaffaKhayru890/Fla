#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./ast.h"

// =========================== Helper Function ===========================

ASTNode *createNode(NodeType type) {
    ASTNode *new_node = (ASTNode*)calloc(1 ,sizeof(ASTNode));

    if(new_node == NULL) {
        fprintf(stderr, "Error: failed to create new node");
        exit(EXIT_FAILURE);
    }

    new_node->type = type;

    return new_node;
}

void 

// =========================== Create parent node ===========================

ASTNode *createProgramNode() {
    ASTNode *node = createNode(NODE_PROGRAM);

    return node;
}

ASTNode *createModuleNode(char *name) {
    ASTNode *node = createNode(NODE_MODULE);

    node->module.name = strdup(name);

    return node;
}

// =========================== Create function for statement node ===========================

ASTNode *createFunctionDeclarationNode(char *identifier ,char *return_type);

ASTNode *createVariableDeclarationNode(char *identifier ,char *variable_type) {
    ASTNode *node = createNode(NODE_MODULE);

    node->variable_declaration.identifier = strdup(identifier);
    node->variable_declaration.type = strdup(variable_type);

    return node;
}

ASTNode *createIfNode(int elseif_count);
ASTNode *createWhileNode();
ASTNode *createForNode();
ASTNode *createSwitchNode(int case_count);