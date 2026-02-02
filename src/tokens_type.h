#ifndef FLA_TOKENS_TYPE_H
#define FLA_TOKENS_TYPE_H

typedef enum {
    // base keyword
    TOK_KEY_FUN,
    TOK_KEY_IF,
    TOK_KEY_ELSE,
    TOK_KEY_WHILE,
    TOK_KEY_FOR,
    TOK_KEY_SWITCH,
    TOK_KEY_TRUE,
    TOK_KEY_FALSE,

    // unique
    TOK_IDENTIFIER,

    // type keyword
    TOK_TYPE_INT,
    TOK_TYPE_DOUBLE,
    TOK_TYPE_CHAR,
    TOK_TYPE_STRING,
    TOK_TYPE_BOOLEAN,

    // basic operators
    TOK_PLUS, TOK_MINUS, TOK_MULTIPLY, TOK_DIVISION, TOK_MODULO, TOK_EXPONENT,

    // condition 
    TOK_OP_EQ,
    TOK_OP_NEQ,
    TOK_OP_LT,
    TOK_OP_LTE,
    TOK_OP_GT,
    TOK_OP_GTE,

    // single marks
    TOK_OP_UNARY,
    TOK_COMMA,

    // literal
    TOK_STRING,
    TOK_CHAR,
    TOK_INT,
    TOK_DOUBLE,

    // others
    TOK_ERRORS,
    TOK_UNKNOWN,
    TOK_EOF
}TokenType;

#endif