#include "../include/lexer.h"
#include "./unity.h"
#include "./unity_internals.h"

#include "stdio.h"

void setUp(void) {}
void tearDown(void) {}

void test_keyword() {
    struct {
        char *input;
        TokenType type;
    } keywords[] = {
        {"use", TOK_KEY_USE},
        {"fun", TOK_KEY_FUN},
        {"if", TOK_KEY_IF},
        {"else", TOK_KEY_ELSE},
        {"break", TOK_KEY_BREAK},
        {"continue", TOK_KEY_CONTINUE},
        {"while", TOK_KEY_WHILE},
        {"for", TOK_KEY_FOR},
        {"switch", TOK_KEY_SWITCH},
        {"int", TOK_TYPE_INT},
        {"double", TOK_TYPE_DOUBLE},
        {"char", TOK_TYPE_CHAR},
        {"boolean", TOK_TYPE_BOOLEAN},
        {"string", TOK_TYPE_STRING},
        {"true", TOK_KEY_TRUE},
        {"false", TOK_KEY_FALSE},
    };
    
    int size_mark = sizeof(keywords)/sizeof(keywords[0]);

    for(int i = 0; i < size_mark; i++) {
        Lexer lexer;
        Token token;

        createLexer(&lexer, keywords[i].input);

        token = getNextToken(&lexer);
        TEST_ASSERT_EQUAL_STRING(keywords[i].input, token.lexeme);
        TEST_ASSERT_EQUAL(keywords[i].type, token.type);
    }
}

void test_identifier(void) {   
    struct {
        char *input;
        TokenType type;
    } keywords[] = {
        {"main", TOK_IDENTIFIER},
        {"nama_saya", TOK_IDENTIFIER}
    };
    
    int size_mark = sizeof(keywords)/sizeof(keywords[0]);

    for(int i = 0; i < size_mark; i++) {
        Lexer lexer;
        Token token;

        createLexer(&lexer, keywords[i].input);

        token = getNextToken(&lexer);
        TEST_ASSERT_EQUAL_STRING(keywords[i].input, token.lexeme);
        TEST_ASSERT_EQUAL(keywords[i].type, token.type);
    }
} 

void test_string(void) {
    char *source = "\"hello\"";

    Lexer lexer;
    Token token;

    createLexer(&lexer, source);
    
    TEST_ASSERT_EQUAL(TOK_STRING, token.type);
    TEST_ASSERT_EQUAL_STRING("\"hello\"", token.lexeme);
}

void test_number(void) {
    struct {
        char *input;
        TokenType type;
    } keywords[] = {
        {"1", TOK_INT},
        {"123", TOK_INT},
        {"3.14", TOK_DOUBLE},
    };

    int size_mark = sizeof(keywords)/sizeof(keywords[0]);

    for(int i = 0; i < size_mark; i++) {
        Lexer lexer;
        Token token;

        createLexer(&lexer, keywords[i].input);

        token = getNextToken(&lexer);
        TEST_ASSERT_EQUAL_STRING(keywords[i].input, token.lexeme);
        TEST_ASSERT_EQUAL(keywords[i].type, token.type);
    }
}

void test_operators(void) {
    struct {
        char *input;
        TokenType type;
    } keywords[] = {
        {"(", TOK_LPAREN},
        {")", TOK_RPAREN},
        {":", TOK_COLON},
        {"=", TOK_ASSIGNMENT},
        {"+", TOK_PLUS},
        {"-", TOK_MINUS},
        {"*", TOK_MULTIPLY},
        {"/", TOK_DIVISION},
        {"%", TOK_MODULO},
        {",", TOK_COMMA},
        {"<", TOK_OP_LT},
        {">", TOK_OP_GT},
        {"<=", TOK_OP_LTE},
        {">=", TOK_OP_GTE},
        {"*=", TOK_ASSIGN_MULTIPLY},
        {"/=", TOK_ASSIGN_DIVISION},
        {"+=", TOK_ASSIGN_PLUS},
        {"-=", TOK_ASSIGN_MINUS},
        {"++", TOK_INCREMENT},
        {"--", TOK_DECREMENT},
        {"&&", TOK_OP_AND},
        {"||", TOK_OP_OR},
        {"|=", TOK_ASSIGN_BITWISE_OR},
        {"^=", TOK_ASSIGN_BITWISE_XOR},
        {"->", TOK_RARROW},
        {"<<=", TOK_ASSIGN_LEFT_SHIFT},
        {">>=", TOK_ASSIGN_RIGHT_SHIFT},
    };
    
    int size_mark = sizeof(keywords)/sizeof(keywords[0]);

    for(int i = 0; i < size_mark; i++) {
        Lexer lexer;
        Token token;

        createLexer(&lexer, keywords[i].input);

        token = getNextToken(&lexer);
        TEST_ASSERT_EQUAL_STRING(keywords[i].input, token.lexeme);
        TEST_ASSERT_EQUAL(keywords[i].type, token.type);
    }
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_keyword);
    RUN_TEST(test_identifier);
    RUN_TEST(test_number);
    RUN_TEST(test_string);
    RUN_TEST(test_operators);

    printf("\n");

    return UNITY_END();
}