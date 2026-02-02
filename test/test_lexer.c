#include "../src/lexer.h"
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

// void test_string(void) {
//     char *source = "\"hello\"";
//     Lexer *l = init_lexer(source);
    
    
//     Token *t = tokenize(l);
    
//     TEST_ASSERT_EQUAL(TK_STRING, t->type);
//     TEST_ASSERT_EQUAL_STRING("hello", t->literal);
    
//     free_lexer(l);
// }

// void test_number(void) {
//     struct {
//         char *input;
//         TokenType type;
//     } test_case[] = {
//         {"1", TK_NUMBER},
//         {"123", TK_NUMBER},
//         {"3.14", TK_DOUBLE},
//     };

//     int size_test_case = sizeof(test_case)/sizeof(test_case[0]);

//     for(int i = 0; i < size_test_case; i++) {
//         Lexer *l = init_lexer(test_case[i].input);

//         Token *t = tokenize(l);
//         TEST_ASSERT_EQUAL(test_case[i].type, t->type);
//         TEST_ASSERT_EQUAL_STRING(test_case[i].input, t->literal);

//         free_token(t);
//         free_lexer(l);
//     }
// }

// void test_operators(void) {
//     struct {
//         char *input;
//         TokenType type;
//     } operators[] = {
//         {"(", TK_LPAREN},
//         {")", TK_RPAREN},
//         {":", TK_COLON},
//         {"=", TK_ASSIGN},
//         {"+", TK_PLUS},
//         {"-", TK_MINUS},
//         {"*", TK_MULTIPLY},
//         {"/", TK_DIVISION},
//         {"%", TK_MODULO},
//         {",", TK_COMMA},
//         {"<", TK_LESS_THAN},
//         {">", TK_GREATER_THAN},
//         {"<=", TK_LESS_THAN_EQUAL},
//         {">=", TK_GREATER_THAN_EQUAL},
//         {"*=", TK_ASSIGN_MULTIPLY},
//         {"/=", TK_ASSIGN_DIVISION},
//         {"+=", TK_ASSIGN_PLUS},
//         {"-=", TK_ASSIGN_MINUS},
//         {"++", TK_INCREMENT},
//         {"--", TK_DECREMENT},
//         {"&&", TK_BITWISE_AND},
//         {"|=", TK_BITWISE_OR},
//         {"^=", TK_BITWISE_XOR},
//         {"->", TK_RARROW}
//     };
    
//     int size_mark = sizeof(operators)/sizeof(operators[0]);

//     for(int i = 0; i < size_mark; i++) {
//         Lexer *l = init_lexer(operators[i].input);

//         Token *t = tokenize(l);
//         TEST_ASSERT_EQUAL_STRING(operators[i].input, t->literal);
//         TEST_ASSERT_EQUAL(operators[i].type, t->type);

//         free_token(t);
//         free_lexer(l);
//     }
// }

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_keyword);
    RUN_TEST(test_identifier);
    // RUN_TEST(test_number);
    // RUN_TEST(test_string);
    // RUN_TEST(test_operators);

    printf("\n");

    return UNITY_END();
}