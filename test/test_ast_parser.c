#include "../include/lexer.h"
#include "stdio.h"
#include "../include/parser.h"
#include "../src/utils/utils.c"
#include "./unity.h"
#include "./unity_internals.h"

void setUp() {}
void tearDown() {}

void test_function_declaration() {
    char *source = read_file("../example/function_declaration.fla");

    Lexer *l = init_lexer(source);
    Parser *p = init_parser(l);

    ASTNode *program = parser_program(p, l, "main");

    TEST_ASSERT_EQUAL_STRING("main", program->statement.FunctionDeclaration.name);
    TEST_ASSERT_EQUAL_STRING("main", program->statement.FunctionDeclaration.return_type);

    free_node(program);
    free_lexer(l);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_function_declaration);

    return UNITY_END();
};