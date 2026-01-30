#include "../include/lexer.h"
#include "./unity.h"
#include "./unity_internals.h"

#include "stdio.h"

void setUp(void) {}
void tearDown(void) {}

void test_keyword_module(void) {   
    char *code = "module";

    Lexer *l = init_lexer(code);
    Token *t = init_token();

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_KEYWORD_MODULE, t->type);
    TEST_ASSERT_EQUAL_STRING("module", t->literal);

    free_lexer(l);
    free_token(t);
}

void test_keyword_fun(void) {   
    char *code = "fun";

    Lexer *l = init_lexer(code);
    Token *t = init_token();

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_KEYWORD_FUN, t->type);
    TEST_ASSERT_EQUAL_STRING("fun", t->literal);

    free_lexer(l);
    free_token(t);
}

void test_keyword_void(void) {   
    char *code = "void";

    Lexer *l = init_lexer(code);
    Token *t = init_token();

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_KEYWORD_VOID, t->type);
    TEST_ASSERT_EQUAL_STRING("void", t->literal);

    free_lexer(l);
    free_token(t);
}

void test_keyword_do(void) {   
    char *code = "do";

    Lexer *l = init_lexer(code);
    Token *t = init_token();

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_KEYWORD_DO, t->type);
    TEST_ASSERT_EQUAL_STRING("do", t->literal);

    free_lexer(l);
    free_token(t);
}

void test_keyword_end(void) {   
    char *code = "end";

    Lexer *l = init_lexer(code);
    Token *t = init_token();

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_KEYWORD_END, t->type);
    TEST_ASSERT_EQUAL_STRING("end", t->literal);

    free_lexer(l);
    free_token(t);
}

void test_identifier(void) {   
    char *code = "main print";

    Lexer *l = init_lexer(code);
    Token *t = init_token();

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_IDENTIFIER, t->type);
    TEST_ASSERT_EQUAL_STRING("main", t->literal);

    tokenize(l, t);

    TEST_ASSERT_EQUAL(TK_IDENTIFIER, t->type);
    TEST_ASSERT_EQUAL_STRING("print", t->literal);

    free_lexer(l);
    free_token(t);
}

void test_string(void) {
    char *source = "\"hello\"";
    Lexer *l = init_lexer(source);
    Token *t = init_token();
    
    tokenize(l, t);
    
    TEST_ASSERT_EQUAL(TK_STRING, t->type);
    TEST_ASSERT_EQUAL_STRING("hello", t->literal);
    
    free_lexer(l);
    free_token(t);
}

void test_operators(void) {
    char *source = "( ) -> : =";
    Lexer *l = init_lexer(source);
    Token *t = init_token();
    
    tokenize(l, t);
    TEST_ASSERT_EQUAL(TK_LPAREN, t->type);
    
    tokenize(l, t);
    TEST_ASSERT_EQUAL(TK_RPAREN, t->type);
    
    tokenize(l, t);
    TEST_ASSERT_EQUAL(TK_RARROW, t->type);
    
    tokenize(l, t);
    TEST_ASSERT_EQUAL(TK_COLON, t->type);
    
    tokenize(l, t);
    TEST_ASSERT_EQUAL(TK_ASSIGN, t->type);
    
    free_lexer(l);
    free_token(t);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_keyword_module);
    RUN_TEST(test_keyword_fun);
    RUN_TEST(test_keyword_void);
    RUN_TEST(test_keyword_do);
    RUN_TEST(test_keyword_end);
    RUN_TEST(test_identifier);
    RUN_TEST(test_string);
    RUN_TEST(test_operators);

    return UNITY_END();
}