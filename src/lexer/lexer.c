#include "ctype.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "../../include/lexer.h"

#define MAX_LITERAL 256

Lexer *init_lexer(char *input) {
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));

    if(lexer == NULL) {
        fprintf(stderr, "Error: can not init lexer\n");
        exit(EXIT_FAILURE);
    };

    lexer->input = strdup(input);
    lexer->line = 1;
    lexer->column = 1;
    lexer->pos = 0;
    lexer->ch = lexer->input[lexer->pos];

    return lexer;
}

void advanced(Lexer *l) {
    if(l->ch != '\0') {
        l->pos++;
        l->column++;
        l->ch = l->input[l->pos];
    }
}

void skip_whitespace(Lexer *l) {
    while(l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        if(l->ch == '\n') {
            l->line++;
            l->column = 0;
        }

        advanced(l);
    }
}

void create_token(Lexer *l, Token *t, TokenType type, char *literal_char) {
    strcpy(t->literal, literal_char);
    t->type = type;

    advanced(l);
}

void free_lexer(Lexer *l) {
    if(l != NULL) {
        free(l->input);
        free(l);
    }
}

void free_token(Token *t) {
    if(t != NULL) {
        free(t);
    }
}

Token *read_keyword(Lexer *l, Token *t) {
    int pos = 0;
    
    while((isalnum(l->ch) || l->ch == '_') && (pos < MAX_LITERAL-1)) {
        t->literal[pos] = l->ch;
        advanced(l);

        pos++;
    }

    t->literal[pos] = '\0';

    if(strcmp(t->literal, "fun") == 0) {
        t->type = TK_KEYWORD_FUN;

        return t;
    }else if(strcmp(t->literal, "do") == 0) {
        t->type = TK_KEYWORD_DO;

        return t;
    }else if(strcmp(t->literal, "end") == 0) {
        t->type = TK_KEYWORD_END;

        return t;
    }else if(strcmp(t->literal, "var") == 0) {
        t->type = TK_KEYWORD_VAR;

        return t;
    }else if(strcmp(t->literal, "if") == 0) {
        t->type = TK_KEYWORD_IF;

        return t;
    }else if(strcmp(t->literal, "else") == 0) {
        t->type = TK_KEYWORD_ELSE;

        return t;
    }else if(strcmp(t->literal, "switch") == 0) {
        t->type = TK_KEYWORD_SWITCH;

        return t;
    }else if(strcmp(t->literal, "const") == 0) {
        t->type = TK_KEYWORD_CONST;

        return t;
    }else if(strcmp(t->literal, "while") == 0) {
        t->type = TK_KEYWORD_WHILE;

        return t;
    }else if(strcmp(t->literal, "for") == 0) {
        t->type = TK_KEYWORD_FOR;

        return t;
    }else if(strcmp(t->literal, "use") == 0) {
        t->type = TK_KEYWORD_USE;

        return t;
    }else if(strcmp(t->literal, "return") == 0) {
        t->type = TK_KEYWORD_RETURN;

        return t;
    }else if(strcmp(t->literal, "int") == 0) {
        t->type = TK_KEYWORD_INT;

        return t;
    }else if(strcmp(t->literal, "double") == 0) {
        t->type = TK_KEYWORD_DOUBLE;

        return t;
    }else if(strcmp(t->literal, "char") == 0) {
        t->type = TK_KEYWORD_CHAR;

        return t;
    }else if(strcmp(t->literal, "boolean") == 0) {
        t->type = TK_KEYWORD_BOOLEAN;

        return t;
    }else if(strcmp(t->literal, "string") == 0) {
        t->type = TK_KEYWORD_STRING;

        return t;
    }else if(strcmp(t->literal, "true") == 0) {
        t->type = TK_KEYWORD_TRUE;

        return t;
    }else if(strcmp(t->literal, "false") == 0) {
        t->type = TK_KEYWORD_FALSE;

        return t;
    }else {
        t->type = TK_IDENTIFIER;

        return t;
    }
}

Token *read_string(Lexer *l, Token *t) {
    if(l->ch != '"') return NULL;
    
    int pos = 0;

    advanced(l);

    while(l->ch != '"' && l->ch != '\0' && (pos < MAX_LITERAL-1)) {
        t->literal[pos] = l->ch;
        advanced(l);

        pos++;
    }

    if(l->ch == '"') advanced(l);

    t->literal[pos] = '\0';
    t->type = TK_STRING;

    return t;
}

Token *read_char(Lexer *l, Token *t) {
    if(l->ch != '\'') return NULL;
    
    int pos = 0;

    advanced(l);

    while(l->ch != '\'' && l->ch != '\0' && (pos < MAX_LITERAL-1)) {
        t->literal[pos] = l->ch;
        advanced(l);

        pos++;
    }

    if(l->ch == '\'') advanced(l);

    t->literal[pos] = '\0';
    t->type = TK_CHAR;

    return t;
}

Token *read_digit(Lexer *l, Token *t) {
    int pos = 0;
    bool has_dot = false;
    
    while(isdigit(l->ch) && (pos < MAX_LITERAL-1)) {
        t->literal[pos] = l->ch;
        advanced(l);

        pos++;
    }

    if(l->ch == '.' && isdigit(l->input[l->pos+1])) {
        has_dot = true;

        t->literal[pos] = l->ch;
        advanced(l);
        pos++;

        while(isdigit(l->ch) && (pos < MAX_LITERAL-1)) {
            t->literal[pos] = l->ch;
            advanced(l);
            pos++;
        }
    }

    t->literal[pos] = '\0';

    if(has_dot) {
        t->type = TK_DOUBLE;
    }else {
        t->type = TK_NUMBER;
    }

    return t;
}

Token *read_two_char_token(Lexer *l, Token *t, TokenType token_type, char first, char second) {
    if(l == NULL || t == NULL) return NULL;
    
    if(l->ch == first && l->input[l->pos+1] == second && l->input[l->pos+1] != '\0') {
        t->literal[0] = first;
        t->literal[1] = second;
        t->literal[2] = '\0';

        t->type = token_type;

        advanced(l);
        advanced(l);

        return t;
    }

    return NULL;
}

Token *tokenize(Lexer *l) {
    Token *t = (Token *)malloc(sizeof(Token));

    skip_whitespace(l);

    Token *result;

    if((result = read_two_char_token(l, t, TK_EQUAL, '=', '=')) != NULL) return result;
    if((result = read_two_char_token(l, t, TK_NOT_EQUAL, '!', '=')) != NULL) return result;
    if((result = read_two_char_token(l, t, TK_LESS_THAN_EQUAL, '<', '=')) != NULL) return result;
    if((result = read_two_char_token(l, t, TK_GREATER_THAN_EQUAL, '>', '=')) != NULL) return result;

    if((result = read_two_char_token(l, t, TK_ASSIGN_PLUS, '+', '=')) != NULL) return result;
    if((result = read_two_char_token(l, t, TK_ASSIGN_MINUS, '-', '=')) != NULL) return result;
    if((result = read_two_char_token(l, t, TK_ASSIGN_MULTIPLY, '*', '=')) != NULL) return result;
    if((result = read_two_char_token(l, t, TK_ASSIGN_DIVISION, '/', '=')) != NULL) return result;
    if((result = read_two_char_token(l, t, TK_ASSIGN_MODULO, '%', '=')) != NULL) return result;

    if((result = read_two_char_token(l, t, TK_BITWISE_AND, '&', '&')) != NULL) return result;
    if((result = read_two_char_token(l, t, TK_BITWISE_OR, '|', '=')) != NULL) return result;
    if((result = read_two_char_token(l, t, TK_BITWISE_XOR, '^', '=')) != NULL) return result;

    if((result = read_two_char_token(l, t, TK_INCREMENT, '+', '+')) != NULL) return result;
    if((result = read_two_char_token(l, t, TK_DECREMENT, '-', '-')) != NULL) return result;

    if((result = read_two_char_token(l, t, TK_RARROW, '-', '>')) != NULL) return result;

    if(isalpha(l->ch)) {
        return read_keyword(l, t);
    }

    if(l->ch == '"') {
        return read_string(l, t);
    }

    if(l->ch == '\'') {
        return read_char(l, t);
    }

    if(isdigit(l->ch)) {
        return read_digit(l, t);
    }

    switch(l->ch) {
        case '(':
            create_token(l , t, TK_LPAREN, "(");

            return t;
        break;

        case ')':
            create_token(l , t, TK_RPAREN, ")");

            return t;
        break;

        case ':':
            create_token(l , t, TK_COLON, ":");

            return t;
        break;

        case '=':
            create_token(l , t, TK_ASSIGN, "=");

            return t;
        break;

        case '+':
            create_token(l , t, TK_PLUS, "+");

            return t;
        break;

        case '-':
            create_token(l , t, TK_MINUS, "-");

            return t;
        break;

        case '*':
            create_token(l , t, TK_MULTIPLY, "*");

            return t;
        break;

        case '/':
            create_token(l , t, TK_DIVISION, "/");

            return t;
        break;

        case '%':
            create_token(l , t, TK_MODULO, "%");

            return t;
        break;

        case '<':
            create_token(l , t, TK_LESS_THAN, "<");

            return t;
        break;

        case '>':
            create_token(l , t, TK_GREATER_THAN, ">");

            return t;
        break;

        case '^':
            create_token(l , t, TK_EXPONENT, "^");

            return t;
        break;

        case '[':
            create_token(l , t, TK_LSQUARE, "[");

            return t;
        break;

        case ']':
            create_token(l , t, TK_RSQUARE, "]");

            return t;
        break;

        case ',':
            create_token(l , t, TK_COMMA, ",");

            return t;
        break;

        case '?':
            create_token(l , t, TK_TERNARY_OPERATOR, "?");

            return t;
        break;

        case '\0':
            create_token(l , t, TK_EOF, "\0");

            return t;
        break;
    }

    return t;
}