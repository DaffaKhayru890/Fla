#include "../../include/ast.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

// ================================= Helper function =================================

static void freeAtr(void **ptr) {
    if(ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

static void freeNode(ASTNode **node) {
    if(node && *node) {
        freeAstNode(*node, true);
        *node = NULL;
    }
}

static void freeArrayNode(ASTNode ***node) {
    if(node && *node) {
        for(int i = 0; (*node)[i] != NULL; i++) {
            freeAstNode((*node)[i], true);
        }

        free((*node));
        *node = NULL;
    }
}

// ======================================= Free memory =======================================

static void freeLiteralNode(ASTNode *node) {
    if(!node) return;

    switch(node->literal.literal_type) {
        case LITERAL_INT:
            freeAtr((void**)&node->literal.int_value);
        break;

        case LITERAL_DOUBLE:
            freeAtr((void**)&node->literal.double_value);
        break;

        case LITERAL_FLOAT:
            freeAtr((void**)&node->literal.float_value);
        break;

        case LITERAL_CHAR:
            freeAtr((void**)&node->literal.char_value);
        break;

        case LITERAL_STRING:
            freeAtr((void**)&node->literal.string_value);
        break;
    }
}

void freeAstNode(ASTNode *node, bool freeSelf) {
    if(!node) return;

    switch(node->node_type) {
        case NODE_MODULE:
            freeAtr((void **)&node->module.name);
            freeArrayNode(&node->module.body);
        break;

        case NODE_FUNCTION_DECLARATION:
            freeAtr((void **)&node->function_delcaration.identifier);
            freeAtr((void **)&node->function_delcaration.return_type);
            freeNode(&node->function_delcaration.body);
            freeArrayNode(&node->function_delcaration.parameters);
        break;

        case NODE_RETURN_STATEMENT:
            freeNode(&node->return_function.expression);
        break;

        case NODE_BLOCK_STATEMENT:
            freeArrayNode(&node->block_statement.statements);
        break;

        case NODE_VARIABLE_DECLARATION:
            freeAtr((void **)&node->variable_declaration.identifier);
            freeAtr((void **)&node->variable_declaration.type);
            freeNode(&node->variable_declaration.init);
        break;

        case NODE_BREAK_STATEMENT:
        case NODE_CONTINUE_STATEMENT:
            
        break;

        case NODE_IF_STATEMENT:
            freeNode(&node->if_statement.condition);
            freeNode(&node->if_statement.else_branch);
            freeArrayNode(&node->if_statement.elseif_branch);
        break;

        case NODE_WHILE_STATEMENT:
            freeNode(&node->while_statement.condition);
            freeArrayNode(&node->while_statement.body);
        break;

        case NODE_FOR_STATEMENT:
            freeNode(&node->for_statement.condition);
            freeNode(&node->for_statement.preclause);
            freeNode(&node->for_statement.postclause);
            freeArrayNode(&node->for_statement.body);
        break;

        case NODE_SWITCH_STATEMENT:
            freeNode(&node->switch_statement.expression);
            freeArrayNode(&node->switch_statement.body);
        break;

        case NODE_BINARY_EXPRESSION:
            freeAtr((void **)&node->binary.op);
            freeNode(&node->binary.left);
            freeNode(&node->binary.right);
        break;

        case NODE_UNARY_EXPRESSION:
            freeAtr((void **)&node->unary.op);
            freeNode(&node->unary.operand);
        break;

        case NODE_TERNARY_EXPRESSION:
            freeNode(&node->tenary.condition);
            freeNode(&node->tenary.then_expr);
            freeNode(&node->tenary.else_expr);
        break;

        case NODE_GROUPING_EXPRESSION:
            freeNode(&node->grouping.expression);
        break;

        case NODE_COMPOUND_EXPRESSION:
            freeArrayNode(&node->compound.body);
        break;

        case NODE_FUNCTION_CALL_EXPRESSION:
            freeAtr((void **)&node->function_call.function_name);
            freeArrayNode(&node->function_call.arguments);
        break;

        case NODE_LITERAL_EXPRESSION:
            freeLiteralNode(node);
        break;
    }

    if(freeSelf) {
        free(node);
    }
}

void createProgramNode(ASTNode **handle_node) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_PROGRAM;
}

void createModuleNode(ASTNode **handle_node, char *name) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_MODULE;
    (*handle_node)->module.name = strdup(name);
    (*handle_node)->module.body = NULL;
}

// ================================= Statement node =================================

void createFuncDeclNode(ASTNode **handle_node, char *identifier, char *return_type, int param_count) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_FUNCTION_DECLARATION;
    (*handle_node)->function_delcaration.identifier = strdup(identifier);
    (*handle_node)->function_delcaration.return_type = strdup(return_type);
    (*handle_node)->function_delcaration.param_count = param_count;
    (*handle_node)->function_delcaration.body = NULL;
    (*handle_node)->function_delcaration.parameters = NULL;
}

void createParamNode(ASTNode **handle_node, char *name, char *type) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_PARAMETER;
    (*handle_node)->parameter.name = strdup(name);
    (*handle_node)->parameter.type = strdup(type);
}

void createReturnNode(ASTNode **handle_node) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_RETURN_STATEMENT;
    (*handle_node)->return_function.expression = NULL;
}

void createBlockNode(ASTNode **handle_node, int statements_count) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_BLOCK_STATEMENT;
    (*handle_node)->block_statement.statements = NULL;
    (*handle_node)->block_statement.statements_count = statements_count;
}

void createVarDeclNode(ASTNode **handle_node, char *identifier, char *type, VarType variable_type) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_VARIABLE_DECLARATION;
    (*handle_node)->variable_declaration.identifier = strdup(identifier);
    (*handle_node)->variable_declaration.type = strdup(type);
    (*handle_node)->variable_declaration.init = NULL;
    (*handle_node)->variable_declaration.variable_type = variable_type;
}

void createIfNode(ASTNode **handle_node, int elseif_count) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_IF_STATEMENT;
    (*handle_node)->if_statement.elseif_count = elseif_count;
    (*handle_node)->if_statement.else_branch = NULL;
    (*handle_node)->if_statement.condition = NULL;
    (*handle_node)->if_statement.elseif_branch = NULL;
}

void createWhileNode(ASTNode **handle_node) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_WHILE_STATEMENT;
    (*handle_node)->while_statement.condition = NULL;
    (*handle_node)->while_statement.body = NULL;
}

void createForNode(ASTNode **handle_node) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_FOR_STATEMENT;
    (*handle_node)->for_statement.body = NULL;
    (*handle_node)->for_statement.condition = NULL;
    (*handle_node)->for_statement.postclause = NULL;
    (*handle_node)->for_statement.preclause = NULL;
}

void createBreakNode(ASTNode **handle_node) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_BREAK_STATEMENT;
}

void createContinueNode(ASTNode **handle_node) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_CONTINUE_STATEMENT;
}

void createSwitchNode(ASTNode **handle_node, int case_count) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_SWITCH_STATEMENT;
    (*handle_node)->switch_statement.case_count = case_count;
    (*handle_node)->switch_statement.expression = NULL;
    (*handle_node)->switch_statement.body = NULL;
}

// ============================== Expression node ==============================

void createBinaryNode(ASTNode **handle_node, char *op) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_BINARY_EXPRESSION;
    (*handle_node)->binary.op = strdup(op);
    (*handle_node)->binary.left = NULL;
    (*handle_node)->binary.right = NULL;
}

void createUnaryNode(ASTNode **handle_node, char *op) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_UNARY_EXPRESSION;
    (*handle_node)->unary.op = strdup(op);
    (*handle_node)->unary.operand = NULL;
}

void createTenaryNode(ASTNode **handle_node) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_TERNARY_EXPRESSION;
    (*handle_node)->tenary.condition = NULL;
    (*handle_node)->tenary.else_expr = NULL;
    (*handle_node)->tenary.then_expr = NULL;
}

void createGroupingNode(ASTNode **handle_node) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_GROUPING_EXPRESSION;
    (*handle_node)->grouping.expression = NULL;
}

void createCompoundNode(ASTNode **handle_node, int count, int capacity) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_COMPOUND_EXPRESSION;
    (*handle_node)->compound.count = count;
    (*handle_node)->compound.capacity = capacity;
    (*handle_node)->compound.body = NULL;
}

void createFunctionCallNode(ASTNode **handle_node, int arg_count) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_FUNCTION_CALL_EXPRESSION;
    (*handle_node)->function_call.arg_count = arg_count;
    (*handle_node)->function_call.arguments = NULL;
}

void createArgumentNode(ASTNode **handle_node) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_ARGUMENT;
    (*handle_node)->argument.literal = NULL;
}

void createLiteralNode(ASTNode **handle_node, LiteralType literal_type, void *value) {
    *handle_node = (ASTNode*)malloc(sizeof(ASTNode));

    (*handle_node)->node_type = NODE_LITERAL_EXPRESSION;
    (*handle_node)->literal.literal_type = literal_type;

    switch(literal_type) {
        case LITERAL_INT:
            (*handle_node)->literal.int_value = value;
        break;

        case LITERAL_DOUBLE:    
            (*handle_node)->literal.double_value = value;
        break;

        case LITERAL_FLOAT:
            (*handle_node)->literal.float_value = value;
        break;

        case LITERAL_CHAR:
            (*handle_node)->literal.char_value = value;
        break;

        case LITERAL_STRING:
            (*handle_node)->literal.string_value = value;
        break;
    }

    
    
    
    
}
