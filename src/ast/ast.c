#include "../../include/ast.h"
#include "../../include/memory.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

static void freeLiteralNode(ASTNode *node) {
    if(!node) return;

    switch(node->literal.literal_type) {
        case LITERAL_INT:

        break;

        case LITERAL_DOUBLE:
            
        break;

        case LITERAL_CHAR:
            
        break;

        case LITERAL_STRING:
            
        break;

        case LITERAL_BOOLEAN:
            
        break;
    }
}

static void freeCurrentNode(ASTNode *node, ASTNode *current_node) {
    if(!node || !current_node) return;

    if(current_node) free(current_node);
}

void freeAstNode(ASTNode *node, bool freeSelf) {
    if(node == NULL) return;

    switch(node->node_type) {
        case NODE_MODULE:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->module.name);
            freeCurrentNode(node, node->module.body);
        break;

        case NODE_FUNCTION_DECLARATION:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->function_delcaration.identifier);
            freeCurrentNode(node, node->function_delcaration.return_type);
            freeCurrentNode(node, node->function_delcaration.arguments);
        break;

        case NODE_RETURN_STATEMENT:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->return_function.return_value);
        break;

        case NODE_BLOCK_STATEMENT:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->block_statement.statements);
        break;

        case NODE_VARIABLE_DECLARATION:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->variable_declaration.identifier);
            freeCurrentNode(node, node->variable_declaration.type);
        break;

        case NODE_BREAK_STATEMENT:
            freeCurrentNode(node, node->node_type);
        break;

        case NODE_CONTINUE_STATEMENT:
            freeCurrentNode(node, node->node_type);
        break;

        case NODE_IF_STATEMENT:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->if_statement.condition);
            freeCurrentNode(node, node->if_statement.else_branch);
            freeCurrentNode(node, node->if_statement.then_branch);
        break;

        case NODE_WHILE_STATEMENT:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->while_statement.condition);
            freeCurrentNode(node, node->while_statement.body);
        break;

        case NODE_FOR_STATEMENT:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->for_statement.condition);
            freeCurrentNode(node, node->for_statement.preclause);
            freeCurrentNode(node, node->for_statement.postclause);
            freeCurrentNode(node, node->for_statement.body);
        break;

        case NODE_SWITCH_STATEMENT:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->switch_statement.expression);
            freeCurrentNode(node, node->switch_statement.body);
        break;

        case NODE_IDENTIFIER_EXPRESSION:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->identifier.name);
        break;

        case NODE_BINARY_EXPRESSION:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->binary.op);
            freeCurrentNode(node, node->binary.left);
            freeCurrentNode(node, node->binary.right);
        break;

        case NODE_UNARY_EXPRESSION:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->unary.op);
            freeCurrentNode(node, node->unary.operand);
        break;

        case NODE_TERNARY_EXPRESSION:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->tenary.condition);
            freeCurrentNode(node, node->tenary.else_expr);
            freeCurrentNode(node, node->tenary.then_expr);
        break;

        case NODE_GROUPING_EXPRESSION:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->grouping.expression);
        break;

        case NODE_COMPOUND_EXPRESSION:
            freeCurrentNode(node, node->node_type);
        break;

        case NODE_FUNCTION_CALL_EXPRESSION:
            freeCurrentNode(node, node->node_type);
            freeCurrentNode(node, node->function_call.function_name);
            freeCurrentNode(node, node->function_call.arguments);
        break;

        case NODE_LITERAL_EXPRESSION:
            freeLiteralNode;
        break;
    }

    if(freeSelf) {
        FREE(ASTNode, node);
    }
}

// ================================= Statement node =================================

void createProgramNode(ASTNode **handle_node) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_PROGRAM;
    
    return handle_node;
}

void createModuleNode(ASTNode **handle_node, char *name) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_MODULE;
    (*handle_node)->module.name = strdup(name);

}

void createFuncDeclNode(ASTNode **handle_node, char *identifier, char *return_type, int arg_count, int capacity) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_FUNCTION_DECLARATION;
    (*handle_node)->function_delcaration.identifier = strdup(identifier);
    (*handle_node)->function_delcaration.return_type = strdup(return_type);
    (*handle_node)->function_delcaration.arg_count = arg_count;
    (*handle_node)->function_delcaration.arg_capacity = capacity;

}

void createReturnNode(ASTNode **handle_node) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_RETURN_STATEMENT;

}

void createBlockNode(ASTNode **handle_node) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_BLOCK_STATEMENT;

}

void createVarDeclNode(ASTNode **handle_node, char *identifier, char *type) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_VARIABLE_DECLARATION;
    (*handle_node)->variable_declaration.identifier = strdup(identifier);
    (*handle_node)->variable_declaration.type = strdup(type);

}

void createIfNode(ASTNode **handle_node, int elseif_count) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_IF_STATEMENT;
    (*handle_node)->if_statement.elseif_count = elseif_count;

}

void createWhileNode(ASTNode **handle_node) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_WHILE_STATEMENT;

}

void createForNode(ASTNode **handle_node) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_FOR_STATEMENT;

}

void createBreakNode(ASTNode **handle_node) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_BREAK_STATEMENT;

}

void createContinueNode(ASTNode **handle_node) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_CONTINUE_STATEMENT;

}

void createSwitchNode(ASTNode **handle_node, int case_count) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_SWITCH_STATEMENT;
    (*handle_node)->switch_statement.case_count = case_count;
}

void addModuleToProgram(ASTNode *program, ASTNode *module) {
    if(program != NODE_PROGRAM) {
        fprintf(stderr, "Error: not program node");
        exit(EXIT_FAILURE);
    }
}

void add

// ============================== Expression node ==============================

void createIdentifierNode(ASTNode **handle_node, char *name) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_IDENTIFIER_EXPRESSION;
    (*handle_node)->identifier.name = strdup(name);
}

void createBinaryNode(ASTNode **handle_node, char *op) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_BINARY_EXPRESSION;
    (*handle_node)->binary.op = strdup(op);
}

void createUnaryNode(ASTNode **handle_node, char *op) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_UNARY_EXPRESSION;
    (*handle_node)->unary.op = strdup(op);
}

void createTenaryNode(ASTNode **handle_node) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_TERNARY_EXPRESSION;
}

void createGroupingNode(ASTNode **handle_node) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_GROUPING_EXPRESSION;
}

void createCompoundNode(ASTNode **handle_node, int count, int capacity) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_COMPOUND_EXPRESSION;
    (*handle_node)->compound.count = count;
    (*handle_node)->compound.capacity = capacity;
}

void createFunctionCallNode(ASTNode **handle_node, char *function_name, int arg_count, int arg_capacity) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_FUNCTION_CALL_EXPRESSION;
    (*handle_node)->function_call.function_name = strdup(function_name);
    (*handle_node)->function_call.arg_count = arg_count;
    (*handle_node)->function_call.arg_capacity = arg_capacity;
}

void createLiteralNode(ASTNode **handle_node, LiteralType literal_type) {
    *handle_node = ALLOCATE(ASTNode, 1);

    (*handle_node)->node_type = NODE_LITERAL_EXPRESSION;
    (*handle_node)->literal.literal_type = literal_type;
}
