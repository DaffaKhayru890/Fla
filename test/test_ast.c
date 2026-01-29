#include "../include/ast.h"
#include "stdio.h"
#include "./unity.h"
#include "./unity_internals.h"

void setUp(void) {}
void tearDown(void) {}

void test_root_node(void) {
    ASTNode *root = create_root_node();

    TEST_ASSERT_EQUAL(NODE_ROOT, root->type);
    TEST_ASSERT_EQUAL(NULL, root->children);
    TEST_ASSERT_EQUAL_INT(0, root->child_count);

    free_node(root);
}

void test_module_node(void) {
    ASTNode *root = create_root_node();
    ASTNode *module = create_module_node(root, "main");

    TEST_ASSERT_EQUAL(NODE_MODULE, module->type);
    TEST_ASSERT_EQUAL(NULL, module->children);
    TEST_ASSERT_EQUAL_INT(0, module->child_count);
    TEST_ASSERT_EQUAL_STRING("main", module->module.name);

    free_node(root);
}

void test_function_declaration_node(void) {
    ASTNode *root = create_root_node();
    ASTNode *module = create_module_node(root, "main");
    ASTNode *function = create_function_declaration_node(module, NULL, "main", "void");

    TEST_ASSERT_EQUAL(NODE_FUNCTION_DECLARATION, function->type);
    TEST_ASSERT_EQUAL(NULL, function->children);
    TEST_ASSERT_EQUAL_INT(0, function->child_count);
    TEST_ASSERT_EQUAL_STRING("main", function->function_declaration.identifier);
    TEST_ASSERT_EQUAL_STRING("void", function->function_declaration.return_type);

    free_node(root);
}

void test_block_node(void) {
    ASTNode *root = create_root_node();
    ASTNode *module = create_module_node(root, "main");
    ASTNode *function = create_function_declaration_node(module, NULL, "main", "void");
    ASTNode *block = create_block_node(function);

    TEST_ASSERT_EQUAL(NODE_BLOCK, block->type);
    TEST_ASSERT_EQUAL(NULL, block->children);
    TEST_ASSERT_EQUAL_INT(0, block->child_count);

    free_node(root);
}

void test_function_call_node(void) {
    ASTNode *root = create_root_node();
    ASTNode *module = create_module_node(root, "main");
    ASTNode *function = create_function_declaration_node(module, NULL, "main", "void");
    ASTNode *block = create_block_node(function);
    ASTNode *function_call = create_function_call_node(block, "say");

    TEST_ASSERT_EQUAL(NODE_FUNCTION_CALL, function_call->type);
    TEST_ASSERT_EQUAL(NULL, function_call->children);
    TEST_ASSERT_EQUAL_INT(0, function_call->child_count);
    TEST_ASSERT_EQUAL_STRING("say", function_call->function_call_node.identifier);

    free_node(root);
}

void test_argument_node(void) {
    ASTNode *root = create_root_node();
    ASTNode *module = create_module_node(root, "main");
    ASTNode *function = create_function_declaration_node(module, NULL, "main", "void");
    ASTNode *block = create_block_node(function);
    ASTNode *function_call = create_function_call_node(block, "say");
    ASTNode *argument = create_argument_node(function_call);

    TEST_ASSERT_EQUAL(NODE_ARGUMENT, argument->type);
    TEST_ASSERT_EQUAL(NULL, argument->child);

    free_node(root);
}

void test_string_literal_node(void) {
    ASTNode *root = create_root_node();
    ASTNode *module = create_module_node(root, "main");
    ASTNode *function = create_function_declaration_node(module, NULL, "main", "void");
    ASTNode *block = create_block_node(function);
    ASTNode *function_call = create_function_call_node(block, "say");
    ASTNode *argument = create_argument_node(function_call);
    ASTNode *string_literal = create_string_literal_node(argument, "Hello");

    TEST_ASSERT_EQUAL(NODE_STRING_LITERAL, string_literal->type);
    TEST_ASSERT_EQUAL_STRING("Hello", string_literal->string_literal.value);

    free_node(root);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_root_node);
    RUN_TEST(test_module_node);
    RUN_TEST(test_function_declaration_node);
    RUN_TEST(test_block_node);
    RUN_TEST(test_function_call_node);
    RUN_TEST(test_argument_node);
    RUN_TEST(test_string_literal_node);

    return UNITY_END();
};