#include "../include/parser.h"
#include "../src/utils/utils.c"
#include "./unity.h"
#include "./unity_internals.h"

#include "stdio.h"

void setUp(void) {}
void tearDown(void) {}

void test_parse_module() {
    char *source_code = read_file("../example/hello.vla");

    Lexer *lexer = init_lexer(source_code);
    Token *token = init_token();

    Parser *parser = init_parser(lexer, token);

    ASTNode *root_node = create_root_node();

    ASTNode *module = parser_module(root_node, parser, lexer, token);

    TEST_ASSERT_EQUAL(NODE_ROOT, root_node->type);

    TEST_ASSERT_EQUAL(NODE_MODULE, module->type);
    TEST_ASSERT_EQUAL_STRING("main", module->module.name);

    free_lexer(lexer);
    free_parser(parser);
}

void test_parse_module() {
    char *source_code = read_file("../example/hello.vla");

    Lexer *lexer = init_lexer(source_code);
    Token *token = init_token();

    Parser *parser = init_parser(lexer, token);

    ASTNode *root_node = create_root_node();

    ASTNode *module = parser_module(root_node, parser, lexer, token);

    TEST_ASSERT_EQUAL(NODE_ROOT, root_node->type);

    TEST_ASSERT_EQUAL(NODE_MODULE, module->type);
    TEST_ASSERT_EQUAL_STRING("main", module->module.name);

    free_lexer(lexer);
    free_parser(parser);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_parse_module);

    return UNITY_END();
}