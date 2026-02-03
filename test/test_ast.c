#include "./ast.h"

void traverseAST(ASTNode *node, int depth) {
    if(!node) return;

    for(int i = 0; i < depth; i++) printf("  "); // indent
    printf("Node type: %d\n", node->type);

    // traverse children
    for(ASTNode *c = node->child; c; c = c->sibling) {
        traverseAST(c, depth + 1);
    }
}

int main() {
    ASTNode *program = createProgramNode();
    ASTNode *module = createModuleNode("main");

    traverseAST(program, 1);

    return 0;
}