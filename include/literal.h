#ifndef FLA_LITERAL_H
#define FLA_LITERAL_H

#include "../../include/node.h"

typedef enum {
    LITERAL_INT,
    LITERAL_DOUBLE,
    LITERAL_CHAR,
    LITERAL_STRING,
    LITERAL_BOOLEAN
}LiteralType;

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_BOOLEAN
}DataType;

typedef struct {
    union {
        int int_value;
        double double_value;
        char char_value;
        char *string_value;
        bool bool_value;
    };
}Literal;

#endif