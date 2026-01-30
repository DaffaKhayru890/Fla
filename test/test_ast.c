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

    ASTNode *module = create_module_node("main");
    add_child_to_parent(root, module);

    TEST_ASSERT_EQUAL(NODE_MODULE, module->type);
    TEST_ASSERT_EQUAL(NULL, module->children);
    TEST_ASSERT_EQUAL_INT(0, module->child_count);
    TEST_ASSERT_EQUAL_STRING("main", module->module.name);
    TEST_ASSERT_EQUAL_PTR(module, root->children[0]);

    free_node(module);
}

void test_function_declaration_node(void) {
    ASTNode *module = create_module_node("main");

    ASTNode *function = create_function_declaration_node("main", "void");
    add_child_to_parent(module, function);

    TEST_ASSERT_EQUAL(NODE_FUNCTION_DECLARATION, function->type);
    TEST_ASSERT_EQUAL(NULL, function->children);
    TEST_ASSERT_EQUAL_INT(0, function->child_count);
    TEST_ASSERT_EQUAL_STRING("main", function->function_declaration.identifier);
    TEST_ASSERT_EQUAL_STRING("void", function->function_declaration.return_type);
    TEST_ASSERT_EQUAL_PTR(function, module->children[0]);

    free_node(function);
}

void test_block_node(void) {
    ASTNode *function = create_function_declaration_node("main", "void");

    ASTNode *block = create_block_node();
    add_child_to_parent(function, block);

    TEST_ASSERT_EQUAL(NODE_BLOCK, block->type);
    TEST_ASSERT_EQUAL(NULL, block->children);
    TEST_ASSERT_EQUAL_INT(0, block->child_count);
    TEST_ASSERT_EQUAL_PTR(block, function->children[0]);

    free_node(block);
}

void test_function_call_node(void) {
    ASTNode *block = create_block_node();

    ASTNode *function_call = create_function_call_node("say");
    add_child_to_parent(block, function_call);

    TEST_ASSERT_EQUAL(NODE_FUNCTION_CALL, function_call->type);
    TEST_ASSERT_EQUAL(NULL, function_call->children);
    TEST_ASSERT_EQUAL_INT(0, function_call->child_count);
    TEST_ASSERT_EQUAL_STRING("say", function_call->function_call_node.identifier);
    TEST_ASSERT_EQUAL_PTR(function_call, block->children[0]);

    free_node(function_call);
}

void test_argument_node(void) {
    ASTNode *argument = create_argument_node();

    TEST_ASSERT_EQUAL(NODE_ARGUMENT, argument->type);
    TEST_ASSERT_EQUAL(NULL, argument->child);

    free_node(argument);
}

void test_string_literal_node(void) {
    ASTNode *string_literal = create_string_literal_node("Hello");

    TEST_ASSERT_EQUAL(NODE_STRING_LITERAL, string_literal->type);
    TEST_ASSERT_EQUAL_STRING("Hello", string_literal->string_literal.value);

    free_node(string_literal);
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