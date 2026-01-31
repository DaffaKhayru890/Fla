#include "../include/lexer.h"
#include "./unity.h"
#include "./unity_internals.h"
#include "../include/utils.h"

#include "stdio.h"

void setUp(void) {}
void tearDown(void) {}

void test_keyword_use(void) {   
    char *code = "use";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_USE, t->type);
    TEST_ASSERT_EQUAL_STRING("use", t->literal);

    free_lexer(l);
}

void test_keyword_fun(void) {   
    char *code = "fun";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_FUN, t->type);
    TEST_ASSERT_EQUAL_STRING("fun", t->literal);

    free_lexer(l);
}

void test_keyword_void(void) {   
    char *code = "void";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_VOID, t->type);
    TEST_ASSERT_EQUAL_STRING("void", t->literal);

    free_lexer(l);
}

void test_keyword_do(void) {   
    char *code = "do";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_DO, t->type);
    TEST_ASSERT_EQUAL_STRING("do", t->literal);

    free_lexer(l);
}

void test_keyword_end(void) {   
    char *code = "end";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_END, t->type);
    TEST_ASSERT_EQUAL_STRING("end", t->literal);

    free_lexer(l);
}

void test_keyword_var(void) {   
    char *code = "var";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_VAR, t->type);
    TEST_ASSERT_EQUAL_STRING("var", t->literal);

    free_lexer(l);
}

void test_keyword_const(void) {   
    char *code = "const";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_CONST, t->type);
    TEST_ASSERT_EQUAL_STRING("const", t->literal);

    free_lexer(l);
}

void test_keyword_if(void) {   
    char *code = "if";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_IF, t->type);
    TEST_ASSERT_EQUAL_STRING("if", t->literal);

    free_lexer(l);
}

void test_keyword_switch(void) {   
    char *code = "switch";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_SWITCH, t->type);
    TEST_ASSERT_EQUAL_STRING("switch", t->literal);

    free_lexer(l);
}

void test_keyword_else(void) {   
    char *code = "else";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_STRING, t->type);
    TEST_ASSERT_EQUAL_STRING("else", t->literal);

    free_lexer(l);
}

void test_keyword_int(void) {   
    char *code = "int";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_INT, t->type);
    TEST_ASSERT_EQUAL_STRING("int", t->literal);

    free_lexer(l);
}

void test_keyword_double(void) {   
    char *code = "double";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_DOUBLE, t->type);
    TEST_ASSERT_EQUAL_STRING("double", t->literal);

    free_lexer(l);
}

void test_keyword_char(void) {   
    char *code = "char";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_CHAR, t->type);
    TEST_ASSERT_EQUAL_STRING("char", t->literal);

    free_lexer(l);
}

void test_keyword_string(void) {   
    char *code = "string";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_STRING, t->type);
    TEST_ASSERT_EQUAL_STRING("string", t->literal);

    free_lexer(l);
}

void test_keyword_for(void) {   
    char *code = "for";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_FOR, t->type);
    TEST_ASSERT_EQUAL_STRING("for", t->literal);

    free_lexer(l);
}

void test_keyword_while(void) {   
    char *code = "while";

    Lexer *l = init_lexer(code);

    Token *t = tokenize(l);

    TEST_ASSERT_EQUAL(TK_KEYWORD_WHILE, t->type);
    TEST_ASSERT_EQUAL_STRING("while", t->literal);

    free_lexer(l);
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

void test_operators(void) {
    char *source = "( ) -> : = + - * / % == != < > <= >= || && ^";
    Lexer *l = init_lexer(source);
    
    Token *t1 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_LPAREN, t1->type);
    
    Token *t2 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_RPAREN, t2->type);
    
    Token *t3 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_RARROW, t3->type);
    
    Token *t4 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_COLON, t4->type);
    
    Token *t5 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_ASSIGN, t5->type);

    Token *t6 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_PLUS, t6->type);

    Token *t7 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_MINUS, t7->type);

    Token *t8 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_MULTIPLY, t8->type);

    Token *t9 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_DIVISION, t9->type);

    Token *t10 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_MODULO, t10->type);

    Token *t11 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_EQUAL, t11->type);

    Token *t12 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_NOT_EQUAL, t12->type);

    Token *t13 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_LESS_THAN, t13->type);

    Token *t14 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_GREATER_THAN, t14->type);

    Token *t15 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_LESS_THAN_EQUAL, t15->type);

    Token *t16 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_GREATER_THAN_EQUAL, t16->type);
    
    Token *t17 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_OR, t17->type);

    Token *t18 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_AND, t18->type);

    Token *t19 = tokenize(l);
    TEST_ASSERT_EQUAL(TK_EXPONENT, t19->type);

    free_lexer(l);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_keyword_use);
    RUN_TEST(test_keyword_fun);
    RUN_TEST(test_keyword_void);
    RUN_TEST(test_keyword_do);
    RUN_TEST(test_keyword_end);
    RUN_TEST(test_keyword_if);
    RUN_TEST(test_keyword_const);
    RUN_TEST(test_keyword_var);
    RUN_TEST(test_keyword_int);
    RUN_TEST(test_keyword_double);
    RUN_TEST(test_keyword_char);
    RUN_TEST(test_keyword_string);
    RUN_TEST(test_keyword_for);
    RUN_TEST(test_keyword_switch);
    RUN_TEST(test_keyword_while);
    RUN_TEST(test_keyword_switch);
    RUN_TEST(test_identifier);
    RUN_TEST(test_string);
    RUN_TEST(test_operators);

    printf("\n");

    return UNITY_END();
}