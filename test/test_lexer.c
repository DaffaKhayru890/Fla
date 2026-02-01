#include "../include/lexer.h"
#include "./unity.h"
#include "./unity_internals.h"
#include "../include/utils.h"

#include "stdio.h"

void setUp(void) {}
void tearDown(void) {}

void test_keyword() {
    struct {
        char *input;
        TokenType type;
    } keywords[] = {
        {"use", TK_KEYWORD_USE},
        {"fun", TK_KEYWORD_FUN},
        {"do", TK_KEYWORD_DO},
        {"end", TK_KEYWORD_END},
        {"do", TK_KEYWORD_DO},
        {"if", TK_KEYWORD_IF},
        {"else", TK_KEYWORD_ELSE},
        {"while", TK_KEYWORD_WHILE},
        {"for", TK_KEYWORD_FOR},
        {"switch", TK_KEYWORD_SWITCH},
        {"int", TK_KEYWORD_INT},
        {"double", TK_KEYWORD_DOUBLE},
        {"char", TK_KEYWORD_CHAR},
        {"boolean", TK_KEYWORD_BOOLEAN},
        {"string", TK_KEYWORD_STRING},
        {"true", TK_KEYWORD_TRUE},
        {"false", TK_KEYWORD_FALSE},
    };
    
    int size_mark = sizeof(keywords)/sizeof(keywords[0]);

    for(int i = 0; i < size_mark; i++) {
        Lexer *l = init_lexer(keywords[i].input);

        Token *t = tokenize(l);
        TEST_ASSERT_EQUAL_STRING(keywords[i].input, t->literal);
        TEST_ASSERT_EQUAL(keywords[i].type, t->type);

        free_token(t);
        free_lexer(l);
    }
}

void test_identifier(void) {   
    char *code = "main nama_saya";

    Lexer *l = init_lexer(code);
    

    Token *t1 = tokenize(l);

    TEST_ASSERT_EQUAL(TK_IDENTIFIER, t1->type);
    TEST_ASSERT_EQUAL_STRING("main", t1->literal);

    Token *t2 = tokenize(l);

    TEST_ASSERT_EQUAL(TK_IDENTIFIER, t2->type);
    TEST_ASSERT_EQUAL_STRING("nama_saya", t2->literal);

    free_lexer(l);
} 

void test_string(void) {
    char *source = "\"hello\"";
    Lexer *l = init_lexer(source);
    
    
    Token *t = tokenize(l);
    
    TEST_ASSERT_EQUAL(TK_STRING, t->type);
    TEST_ASSERT_EQUAL_STRING("hello", t->literal);
    
    free_lexer(l);
}

void test_number(void) {
    struct {
        char *input;
        TokenType type;
    } test_case[] = {
        {"1", TK_NUMBER},
        {"123", TK_NUMBER},
        {"3.14", TK_DOUBLE},
    };

    int size_test_case = sizeof(test_case)/sizeof(test_case[0]);

    for(int i = 0; i < size_test_case; i++) {
        Lexer *l = init_lexer(test_case[i].input);

        Token *t = tokenize(l);
        TEST_ASSERT_EQUAL(test_case[i].type, t->type);
        TEST_ASSERT_EQUAL_STRING(test_case[i].input, t->literal);

        free_token(t);
        free_lexer(l);
    }
}

void test_operators(void) {
    struct {
        char *input;
        TokenType type;
    } operators[] = {
        {"(", TK_LPAREN},
        {")", TK_RPAREN},
        {":", TK_COLON},
        {"=", TK_ASSIGN},
        {"+", TK_PLUS},
        {"-", TK_MINUS},
        {"*", TK_MULTIPLY},
        {"/", TK_DIVISION},
        {"%", TK_MODULO},
        {",", TK_COMMA},
        {"<", TK_LESS_THAN},
        {">", TK_GREATER_THAN},
        {"<=", TK_LESS_THAN_EQUAL},
        {">=", TK_GREATER_THAN_EQUAL},
        {"*=", TK_ASSIGN_MULTIPLY},
        {"/=", TK_ASSIGN_DIVISION},
        {"+=", TK_ASSIGN_PLUS},
        {"-=", TK_ASSIGN_MINUS},
        {"++", TK_INCREMENT},
        {"--", TK_DECREMENT},
        {"&&", TK_BITWISE_AND},
        {"|=", TK_BITWISE_OR},
        {"^=", TK_BITWISE_XOR},
        {"->", TK_RARROW}
    };
    
    int size_mark = sizeof(operators)/sizeof(operators[0]);

    for(int i = 0; i < size_mark; i++) {
        Lexer *l = init_lexer(operators[i].input);

        Token *t = tokenize(l);
        TEST_ASSERT_EQUAL_STRING(operators[i].input, t->literal);
        TEST_ASSERT_EQUAL(operators[i].type, t->type);

        free_token(t);
        free_lexer(l);
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