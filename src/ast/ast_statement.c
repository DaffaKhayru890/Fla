#include "../../include/ast.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

ASTNode *create_function_declaration_node(char *name, char *return_type) {
    ASTNode *function_declaration = create_node(NODE_STATEMENT);

    function_declaration->statement.statement_kind = STATEMENT_FUNCTION_DECLARATION;
    function_declaration->children = NULL;
    function_declaration->child_count = 0;
    function_declaration->statement.FunctionDeclaration.name = strdup(name);
    function_declaration->statement.FunctionDeclaration.param_count = 0;
    function_declaration->statement.FunctionDeclaration.return_type = strdup(return_type);

    return function_declaration;
}

ASTNode *create_block_node() {
    ASTNode *block = create_node(NODE_STATEMENT);

    block->statement.statement_kind = STATEMENT_BLOCK;
    block->children = NULL;
    block->child_count = 0;
    
    return block;
}

ASTNode *create_variable_declaration_node(char *name, char *type) {
    ASTNode *variable_declaration = create_node(NODE_STATEMENT);

    variable_declaration->statement.statement_kind = STATEMENT_VARIABLE_DECLARATION;
    variable_declaration->children = NULL;
    variable_declaration->child_count = 0;
    variable_declaration->statement.VariableDeclaration.name = strdup(name);
    variable_declaration->statement.VariableDeclaration.return_type = strdup(type);

    return variable_declaration;
}

ASTNode *create_if_node(int else_count) {
    ASTNode *If = create_node(NODE_STATEMENT);

    If->statement.statement_kind = STATEMENT_IF;
    If->children = NULL;
    If->child_count = 0;
    If->statement.If.elseif_count = 0;

    return If;
}

ASTNode *create_while_node() {
    ASTNode *While = create_node(NODE_STATEMENT);

    While->statement.statement_kind = STATEMENT_WHILE;
    While->children = NULL;
    While->child_count = 0;

    return While;
};

ASTNode *create_for_node() {
    ASTNode *For = create_node(NODE_STATEMENT);

    For->statement.statement_kind = STATEMENT_FOR;
    For->children = NULL;
    For->child_count = 0;

    return For;
}

ASTNode *create_switch_node(int case_count) {
    ASTNode *Switch = create_node(NODE_STATEMENT);

    Switch->statement.statement_kind = STATEMENT_SWITCH;
    Switch->children = NULL;
    Switch->child_count = 0;
    Switch->statement.Switch.case_count = 0;

    return Switch;
}

