#include "../include/lexer.h"
#include "./unity.h"
#include "./unity_internals.h"

#include "stdio.h"

void setUp(void) {}
void tearDown(void) {}

void test_keyword_fun(void) {   
    char *code = "fun";

    Lexer *l = init_lexer(code);
    Token *t = init_token();

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_KEYWORD, t->type);
    TEST_ASSERT_EQUAL_STRING("fun", t->literal);

    free_lexer(l, t);
}

void test_keyword_void(void) {   
    char *code = "void";

    Lexer *l = init_lexer(code);
    Token *t = init_token();

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_KEYWORD, t->type);
    TEST_ASSERT_EQUAL_STRING("void", t->literal);

    free_lexer(l, t);
}

void test_keyword_end(void) {   
    char *code = "end";

    Lexer *l = init_lexer(code);
    Token *t = init_token();

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_KEYWORD, t->type);
    TEST_ASSERT_EQUAL_STRING("end", t->literal);

    free_lexer(l, t);
}

void test_identifier(void) {   
    char *code = "main";

    Lexer *l = init_lexer(code);
    Token *t = init_token();

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_IDENTIFIER, t->type);
    TEST_ASSERT_EQUAL_STRING("main", t->literal);

    free_lexer(l, t);
}

void test_string(void) {
    char *source = "\"hello\"";
    Lexer *lexer = init_lexer(source);
    Token *token = init_token();
    
    tokenize(lexer, token);
    
    TEST_ASSERT_EQUAL(TK_STRING, token->type);
    TEST_ASSERT_EQUAL_STRING("hello", token->literal);
    
    free_lexer(lexer, token);
}

void test_operators(void) {
    char *source = "( ) -> : =";
    Lexer *lexer = init_lexer(source);
    Token *token = init_token();
    
    tokenize(lexer, token);
    TEST_ASSERT_EQUAL(TK_LPAREN, token->type);
    
    tokenize(lexer, token);
    TEST_ASSERT_EQUAL(TK_RPAREN, token->type);
    
    tokenize(lexer, token);
    TEST_ASSERT_EQUAL(TK_RARROW, token->type);
    
    tokenize(lexer, token);
    TEST_ASSERT_EQUAL(TK_COLON, token->type);
    
    tokenize(lexer, token);
    TEST_ASSERT_EQUAL(TK_ASSIGN, token->type);
    
    free_lexer(lexer, token);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_keyword_fun);
    RUN_TEST(test_keyword_void);
    RUN_TEST(test_keyword_end);
    RUN_TEST(test_identifier);
    RUN_TEST(test_string);
    RUN_TEST(test_operators);

    return UNITY_END();
}