#ifndef FLA_TOKENS_TYPE_H
#define FLA_TOKENS_TYPE_H

typedef enum {
    // base keyword
    TOK_KEY_USE,
    TOK_KEY_FUN,
    TOK_KEY_VAR,
    TOK_KEY_CONST,
    TOK_KEY_IF,
    TOK_KEY_ELSE,
    TOK_KEY_BREAK,
    TOK_KEY_CONTINUE,
    TOK_KEY_WHILE,
    TOK_KEY_FOR,
    TOK_KEY_SWITCH,
    TOK_KEY_TRUE,
    TOK_KEY_FALSE,

    // delimiters
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LBRACE,
    TOK_RBRACE,
    TOK_LBRACKETS,
    TOK_RBRACKETS,

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
    TOK_OP_AND,
    TOK_OP_OR,

    // single marks
    TOK_OP_UNARY,
    TOK_COMMA,
    TOK_SEMICOLON,
    TOK_COLON,
    TOK_ASSIGNMENT,

    // two chars
    TOK_RARROW,

    // assignment
    TOK_ASSIGN_PLUS,
    TOK_ASSIGN_MINUS,
    TOK_ASSIGN_MULTIPLY,
    TOK_ASSIGN_DIVISION,
    TOK_ASSIGN_MODULO,
    TOK_ASSIGN_BITWISE_AND,
    TOK_ASSIGN_BITWISE_OR,
    TOK_ASSIGN_BITWISE_XOR,
    TOK_ASSIGN_LEFT_SHIFT,
    TOK_ASSIGN_RIGHT_SHIFT,

    // decremeent and increment
    TOK_INCREMENT,
    TOK_DECREMENT,

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