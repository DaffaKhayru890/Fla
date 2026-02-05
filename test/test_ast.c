#include "./unity.h"
#include "./unity_internals.h"

#include "../include/ast.h"

void setUp() {}
void tearDown() {}

void test_all_node()
{
    struct
    {
        NodeType type;
        void *creator_func;
        void *params[7];
        int param_count;
        char *test_name;
    } test_cases[] = {
        {NODE_PROGRAM, createProgramNode, {NULL}, 0, "Program"},
        {NODE_MODULE, createModuleNode, {"main", NULL}, 1, "Module"},
        {NODE_PARAMETER, createParamNode, {"x", "int", NULL}, 2, "Parameter"},
        {NODE_FUNCTION_DECLARATION, createFuncDeclNode, {"func", "void", (void *)0, (void *)10}, 4, "Function Declaration"},
        {NODE_RETURN_STATEMENT, createReturnNode, {NULL}, 0, "Return"},
        {NODE_BLOCK_STATEMENT, createBlockNode, {NULL}, 0, "Block"},
        {NODE_VARIABLE_DECLARATION, createVarDeclNode, {"var", "int", NULL}, 2, "Variable Declaration"},
        {NODE_IF_STATEMENT, createIfNode, {(void *)0, NULL}, 1, "If Statement"},
        {NODE_WHILE_STATEMENT, createWhileNode, {NULL}, 0, "While"},
        {NODE_FOR_STATEMENT, createForNode, {NULL}, 0, "For"},
        {NODE_BREAK_STATEMENT, createBreakNode, {NULL}, 0, "Break"},
        {NODE_CONTINUE_STATEMENT, createContinueNode, {NULL}, 0, "Continue"},
        {NODE_SWITCH_STATEMENT, createSwitchNode, {(void *)0, NULL}, 1, "Switch"},

        {NODE_IDENTIFIER_EXPRESSION, createIdentifierNode, {"name", NULL}, 1, "Identifier"},
        {NODE_BINARY_EXPRESSION, createBinaryNode, {"+", NULL}, 1, "Binary"},
        {NODE_UNARY_EXPRESSION, createUnaryNode, {"-", NULL}, 1, "Unary"},
        {NODE_TERNARY_EXPRESSION, createTenaryNode, {NULL}, 0, "Ternary"},
        {NODE_GROUPING_EXPRESSION, createGroupingNode, {NULL}, 0, "Grouping"},
        {NODE_COMPOUND_EXPRESSION, createCompoundNode, {(void *)0, (void *)10}, 2, "Compound"},
        {NODE_FUNCTION_CALL_EXPRESSION, createFunctionCallNode, {"print", (void *)0, (void *)10}, 3, "Function Call"},

        {NODE_LITERAL_EXPRESSION, createLiteralNode, {(void *)LITERAL_INT, (void *)42, NULL}, 7, "Literal Int"},
        {NODE_LITERAL_EXPRESSION, createLiteralNode, {(void *)LITERAL_DOUBLE, (void *)0, (void *)&(double){3.14}, NULL}, 7, "Literal Double"},
        {NODE_LITERAL_EXPRESSION, createLiteralNode, {(void *)LITERAL_CHAR, NULL, NULL, (void *)'A', NULL}, 7, "Literal Char"},
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++)
    {
        ASTNode *node = NULL;

        // Call creator function based on param count
        switch (test_cases[i].param_count)
        {
        case 0:
            ((void (*)(ASTNode **))test_cases[i].creator_func)(&node);
            break;
        case 1:
            ((void (*)(ASTNode **, void *))test_cases[i].creator_func)(
                &node, test_cases[i].params[0]);
            break;
        case 2:
            ((void (*)(ASTNode **, void *, void *))test_cases[i].creator_func)(
                &node, test_cases[i].params[0], test_cases[i].params[1]);
            break;
        case 3:
            ((void (*)(ASTNode **, void *, void *, void *))test_cases[i].creator_func)(
                &node, test_cases[i].params[0], test_cases[i].params[1], test_cases[i].params[2]);
            break;
        case 4:
            ((void (*)(ASTNode **, void *, void *, void *, void *))test_cases[i].creator_func)(
                &node, test_cases[i].params[0], test_cases[i].params[1],
                test_cases[i].params[2], test_cases[i].params[3]);
            break;
        case 7: // Literal with all params
            ((void (*)(ASTNode **, LiteralType, int, double, char, char *, bool))test_cases[i].creator_func)(
                &node,
                (LiteralType)test_cases[i].params[0],
                (int)(intptr_t)test_cases[i].params[1],
                test_cases[i].params[2] ? *(double *)test_cases[i].params[2] : 0.0,
                (char)(intptr_t)test_cases[i].params[3],
                (char *)test_cases[i].params[4],
                (bool)(intptr_t)test_cases[i].params[5]
            );
            break;
        }

        // Assert
        char msg[100];
        sprintf(msg, "Test failed for: %s", test_cases[i].test_name);
        TEST_ASSERT_NOT_NULL_MESSAGE(node, msg);
        TEST_ASSERT_EQUAL_MESSAGE(test_cases[i].type, node->node_type, msg);

        // Cleanup
        freeAstNode(node, true);
    }
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_all_node);

    return UNITY_END();
}