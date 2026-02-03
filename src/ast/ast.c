#include "../../include/ast.h"
#include "../../include/memory.h"

#include <string.h>
#include <stdbool.h>

static void freeCurrentNode(ASTNode *node, ASTNode *current_node) {
    if(!node || !current_node) return;

    if(current_node) free(current_node);
}

void freeAstNode(ASTNode *node, bool freeSelf) {
    if(node == NULL) return;

    switch(node->node_type) {
        case NODE_MODULE:
            freeCurrentNode(node, node->module.name);
            freeCurrentNode(node, node->module.body);
        break;

        case NODE_FUNCTION_DECLARATION:
            freeCurrentNode(node, node->function_delcaration.identifier);
            freeCurrentNode(node, node->function_delcaration.return_type);
            freeCurrentNode(node, node->function_delcaration.arguments);
        break;

        case NODE_RETURN_STATEMENT:
            freeCurrentNode(node, node->return_function.return_value);
        break;

        case NODE_BLOCK_STATEMENT:
            freeCurrentNode(node, node->block_statement.statements);
        break;

        case NODE_VARIABLE_DECLARATION:
            freeCurrentNode(node, node->variable_declaration.identifier);
            freeCurrentNode(node, node->variable_declaration.type);
        break;

        case NODE_BREAK_STATEMENT:
        break;

        case NODE_CONTINUE_STATEMENT:
        break;

        case NODE_IF_STATEMENT:
            freeCurrentNode(node, node->if_statement.condition);
            freeCurrentNode(node, node->if_statement.else_branch);
            freeCurrentNode(node, node->if_statement.then_branch);
        break;

        case NODE_WHILE_STATEMENT:
            freeCurrentNode(node, node->while_statement.condition);
            freeCurrentNode(node, node->while_statement.body);
        break;

        case NODE_FOR_STATEMENT:
            freeCurrentNode(node, node->for_statement.condition);
            freeCurrentNode(node, node->for_statement.preclause);
            freeCurrentNode(node, node->for_statement.postclause);
            freeCurrentNode(node, node->for_statement.body);
        break;
    }

    if(freeSelf) {
        FREE(ASTNode, node);
    }
}

ASTNode *createProgramNode(ASTNode **handle) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_PROGRAM;
    
    return handle;
}

ASTNode *createModuleNode(ASTNode **handle, char *name) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_MODULE;
    (*handle)->module.name = strdup(name);
    
    return handle;
}

ASTNode *createFuncDeclNode(ASTNode **handle, char *identifier, char *return_type, int arg_count, int capacity) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_FUNCTION_DECLARATION;
    (*handle)->function_delcaration.identifier = strdup(identifier);
    (*handle)->function_delcaration.return_type = strdup(return_type);
    (*handle)->function_delcaration.arg_count = arg_count;
    (*handle)->function_delcaration.arg_capacity = capacity;
    
    return handle;
}

ASTNode *createReturnNode(ASTNode **handle) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_RETURN_STATEMENT;
    
    return handle;
}

ASTNode *createBlockNode(ASTNode **handle) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_BLOCK_STATEMENT;
    
    return handle;
}

ASTNode *createVarDeclNode(ASTNode **handle, char *identifier, char *type) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_VARIABLE_DECLARATION;
    (*handle)->variable_declaration.identifier = strdup(identifier);
    (*handle)->variable_declaration.type = strdup(type);
    
    return handle;
}

ASTNode *createIfNode(ASTNode **handle, int elseif_count) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_IF_STATEMENT;
    (*handle)->if_statement.elseif_count = elseif_count;
    
    return handle;
}

ASTNode *createWhileNode(ASTNode **handle) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_WHILE_STATEMENT;
    
    return handle;
}

ASTNode *createForNode(ASTNode **handle) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_FOR_STATEMENT;
    
    return handle;
}

ASTNode *createBreakNode(ASTNode **handle) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_BREAK_STATEMENT;
    
    return handle;
}

ASTNode *createContinueNode(ASTNode **handle) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_CONTINUE_STATEMENT;
    
    return handle;
}

ASTNode *createSwitchNode(ASTNode **handle, int case_count) {
    *handle = ALLOCATE(ASTNode, 1);

    (*handle)->node_type = NODE_SWITCH_STATEMENT;
    (*handle)->switch_statement.case_count = case_count;

    return handle;
}
