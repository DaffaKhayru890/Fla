#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./ast.h"

// =========================== Helper Function ===========================

static ASTNode *createNode() {
    ASTNode *node = (ASTNode*)calloc(1, sizeof(ASTNode));

    if(node == NULL) {
        fprintf(stderr, "Error: failed to create node");
        exit(EXIT_FAILURE);
    }

    return node;
}

// =========================== Create function for statement node ===========================

ASTNode *createFunctionDeclarationNode(ASTNode **body , char *identifier ,char *return_type) {

}

ASTNode *createVariableDeclarationNode(ASTNode **body, char *identifier ,char *variable_type) {

}

ASTNode *createIfNode(ASTNode *condition, ASTNode **than_branch, ASTNode **else_branch) {

}

ASTNode *createWhileNode(ASTNode *contidion, ASTNode **body) {

}

ASTNode *createForNode(ASTNode *init, ASTNode *condition, ASTNode *postfix, ASTNode**body) {

}

ASTNode *createSwitchNode(ASTNode *expression, ASTNode **body) {

}