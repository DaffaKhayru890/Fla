#ifndef FLA_LITERAL_H
#define FLA_LITERAL_H

#include "./node.h"
#include <stdbool.h>

typedef enum {
    LITERAL_INT,
    LITERAL_DOUBLE,
    LITERAL_FLOAT,
    LITERAL_CHAR,
    LITERAL_STRING,
    LITERAL_BOOLEAN,
}LiteralType;

typedef struct {
    LiteralType literal_type;
    union {
        int *int_value;
        float *float_value;
        double *double_value;
        char *char_value;
        char *string_value;
        bool boolean_value;
    };
}Literal;

#endif