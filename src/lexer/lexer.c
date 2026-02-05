#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "../../include/lexer.h"

// =============================== Helper Function ===============================

static bool isAtEnd(Lexer *l) {
    return l->current == '\0';
}

static char peek(Lexer *l) {
    return l->current;
}

static char peekNext(Lexer *l) {
    return l->input[l->pos+1];
}

static bool match(Lexer *l, char expect) {
    return peek(l) == expect;
}

static bool matchNext(Lexer *l, char expect) {
    return peekNext(l) == expect;
}

static void advanced(Lexer *l) {
    if(!isAtEnd(l)) {
        if(l->current == '\n') {
            l->line++;
            l->col = 0;
        }else {
            l->col++;
        }

        l->pos++;
        l->current = l->input[l->pos];
    }
}

static void skipWhitespace(Lexer *l) {
    while(peek(l) == ' ' || peek(l) == '\n' || peek(l) == '\t' || peek(l) == '\r') {
        advanced(l);
    }
    
}

static void skipComment(Lexer *l) {
    if(peek(l) == '/' && peekNext(l) == '/') {
        advanced(l);
        advanced(l);

        while(peek(l) != '\n' && !isAtEnd(l)) {
            advanced(l);
        }
    }
}

static Token createToken(Lexer *l, char *lexeme ,TokenType type) {
    Token token;

    strncpy(token.lexeme, lexeme, MAX_LITERAL - 1);
    token.type = type;

    return token;
}

static Token createTwoChars(Lexer *l, char first, char second, TokenType type) {
    Token token;
    
    if(peek(l) == first && peekNext(l) == second && peekNext(l) != '\0') {
        token.lexeme[0] = first;
        token.lexeme[1] = second;
        token.lexeme[2] = '\0';

        token.type = type;

        advanced(l);
        advanced(l);
    }

    return token;
}

static Token createThreeChars(Lexer *l, char first, char second, char third ,TokenType type) {
    Token token;
    
    if(peek(l) == first && peekNext(l) == second && l->input[l->pos+2] == third && l->input[l->pos+2] != '\0') {
        token.lexeme[0] = first;
        token.lexeme[1] = second;
        token.lexeme[2] = third;
        token.lexeme[3] = '\0';

        token.type = type;

        advanced(l);
        advanced(l);
        advanced(l);
    }

    return token;
}

static Token scanKeyword(Lexer *l) {
    if(isAtEnd(l)) {
        Token token;

        token.lexeme[0] = '\0';
        token.type = TOK_EOF;

        return token;
    }

    Token token;

    int posLexeme = 0;

    while((isalnum(peek(l)) || peek(l) == '_') && !isAtEnd(l) && posLexeme < MAX_LITERAL - 1) {
        token.lexeme[posLexeme] = l->current;

        advanced(l);
        
        posLexeme++;
    }

    token.lexeme[posLexeme] = '\0';

    if(strcmp(token.lexeme, "use") == 0) return createToken(l, "use", TOK_KEY_USE);
    if(strcmp(token.lexeme, "fun") == 0) return createToken(l, "fun", TOK_KEY_FUN);
    if(strcmp(token.lexeme, "var") == 0) return createToken(l, "var", TOK_KEY_VAR);
    if(strcmp(token.lexeme, "const") == 0) return createToken(l, "const", TOK_KEY_CONST);
    if(strcmp(token.lexeme, "if") == 0) return createToken(l, "if", TOK_KEY_IF);
    if(strcmp(token.lexeme, "else") == 0) return createToken(l, "else", TOK_KEY_ELSE);
    if(strcmp(token.lexeme, "break") == 0) return createToken(l, "break", TOK_KEY_BREAK);
    if(strcmp(token.lexeme, "continue") == 0) return createToken(l, "continue", TOK_KEY_CONTINUE);
    if(strcmp(token.lexeme, "while") == 0) return createToken(l, "while", TOK_KEY_WHILE);
    if(strcmp(token.lexeme, "for") == 0) return createToken(l, "for", TOK_KEY_FOR);
    if(strcmp(token.lexeme, "switch") == 0) return createToken(l, "switch", TOK_KEY_SWITCH);
    if(strcmp(token.lexeme, "true") == 0) return createToken(l, "true", TOK_KEY_TRUE);
    if(strcmp(token.lexeme, "false") == 0) return createToken(l, "false", TOK_KEY_FALSE);
    if(strcmp(token.lexeme, "int") == 0) return createToken(l, "int", TOK_TYPE_INT);
    if(strcmp(token.lexeme, "double") == 0) return createToken(l, "double", TOK_TYPE_DOUBLE);
    if(strcmp(token.lexeme, "char") == 0) return createToken(l, "char", TOK_TYPE_CHAR);
    if(strcmp(token.lexeme, "string") == 0) return createToken(l, "string", TOK_TYPE_STRING);
    if(strcmp(token.lexeme, "boolean") == 0) return createToken(l, "boolean", TOK_TYPE_BOOLEAN);

    token.type = TOK_IDENTIFIER;

    return token;
}

static Token scanString(Lexer *l) {
    if(isAtEnd(l)) {
        Token token;

        token.lexeme[0] = '\0';
        token.type = TOK_EOF;

        return token;
    }

    if(l->current != '"') {
        Token token;

        token.type = TOK_ERROR;

        return token;
    };

    Token token;

    int posLexeme = 0;

    advanced(l);

    while(!isAtEnd(l) && l->current != '"' && posLexeme < MAX_LITERAL - 1) {
        token.lexeme[posLexeme] = l->current;

        advanced(l);

        posLexeme++;
    }

    advanced(l);

    token.lexeme[posLexeme] = '\0';
    token.type = TOK_STRING;

    return token;
}

static Token scanDigit(Lexer *l) {
    if(isAtEnd(l)) {
        Token token;

        token.lexeme[0] = '\0';
        token.type = TOK_EOF;

        return token;
    }

    Token token;

    bool isFloat = false;
    int posLexeme = 0;

    while(isdigit(peek(l)) && posLexeme < MAX_LITERAL - 1) {
        token.lexeme[posLexeme] = l->current;

        advanced(l);

        posLexeme++;
    }

    if(peek(l) == '.' && isdigit(peekNext(l))) {
        isFloat = true;
        token.lexeme[posLexeme++] = '.';
        advanced(l);

        while(isdigit(peek(l))) {
            token.lexeme[posLexeme++] = peek(l);
            advanced(l);
        }
        
    }

    token.lexeme[posLexeme] = '\0';

    token.type = isFloat ? TOK_DOUBLE : TOK_INT;
    
    return token;
}

// =============================== Lexer Function ===============================

void createLexer(Lexer *l, const char *input) {
    l->input = input;
    l->pos = 0;
    l->current = l->input[l->pos];
    l->line = 1;
    l->col = 0;
}

Token getNextToken(Lexer *l) {
    if(isAtEnd(l)) {
        Token token;

        token.type = TOK_EOF;

        return token;
    }

    Token token;

    skipWhitespace(l);
    skipComment(l);
 
    if(match(l, '<') && matchNext(l, '<') && (l->input[l->pos+2] == '=')) 
        return createThreeChars(l, '<', '<', '=', TOK_ASSIGN_LEFT_SHIFT);
    if(match(l, '>') && matchNext(l, '>') && (l->input[l->pos+2] == '=')) 
        return createThreeChars(l, '>', '>', '=', TOK_ASSIGN_RIGHT_SHIFT);

    if(match(l, '-') && matchNext(l, '>')) return createTwoChars(l, '-', '>', TOK_RARROW);
    if(match(l, '=') && matchNext(l, '=')) return createTwoChars(l, '=', '=', TOK_OP_EQ);
    if(match(l, '!') && matchNext(l, '=')) return createTwoChars(l, '!', '=', TOK_OP_NEQ);
    if(match(l, '<') && matchNext(l, '=')) return createTwoChars(l, '<', '=', TOK_OP_LTE);
    if(match(l, '>') && matchNext(l, '=')) return createTwoChars(l, '>', '=', TOK_OP_GTE);
    if(match(l, '&') && matchNext(l, '&')) return createTwoChars(l, '&', '&', TOK_OP_AND);
    if(match(l, '+') && matchNext(l, '=')) return createTwoChars(l, '+', '=', TOK_ASSIGN_PLUS);
    if(match(l, '-') && matchNext(l, '=')) return createTwoChars(l, '-', '=', TOK_ASSIGN_MINUS);
    if(match(l, '*') && matchNext(l, '=')) return createTwoChars(l, '*', '=', TOK_ASSIGN_MULTIPLY);
    if(match(l, '/') && matchNext(l, '=')) return createTwoChars(l, '/', '=', TOK_ASSIGN_DIVISION);
    if(match(l, '%') && matchNext(l, '=')) return createTwoChars(l, '%', '=', TOK_ASSIGN_MODULO);
    if(match(l, '^') && matchNext(l, '=')) return createTwoChars(l, '^', '=', TOK_ASSIGN_BITWISE_XOR);
    if(match(l, '+') && matchNext(l, '+')) return createTwoChars(l, '+', '+', TOK_INCREMENT);
    if(match(l, '-') && matchNext(l, '-')) return createTwoChars(l, '-', '-', TOK_DECREMENT);
    if(match(l, '|') && matchNext(l, '|')) return createTwoChars(l, '|', '|', TOK_OP_OR);
    if(match(l, '|') && matchNext(l, '=')) return createTwoChars(l, '|', '=', TOK_ASSIGN_BITWISE_OR);

    if(isalpha(peek(l))) {
        return scanKeyword(l);
    }

    if(isdigit(peek(l))) {
        return scanDigit(l);
    }

    char ch = l->current;
    advanced(l);

    switch(ch) {
        case '(': return createToken(l, "(", TOK_LPAREN); break;
        case ')': return createToken(l, ")", TOK_RPAREN); break;
        case '{': return createToken(l, "{", TOK_LBRACE); break;
        case '}': return createToken(l, "}", TOK_RBRACE); break;
        case '[': return createToken(l, "[", TOK_LBRACKETS); break;
        case ']': return createToken(l, "]", TOK_RBRACKETS); break;
        case ',': return createToken(l, ",", TOK_COMMA); break;
        case ':': return createToken(l, ":", TOK_COLON); break;
        case ';': return createToken(l, ";", TOK_SEMICOLON); break;
        case '?': return createToken(l, "?", TOK_OP_UNARY); break;
        case '=': return createToken(l, "=", TOK_ASSIGNMENT); break;
        case '%': return createToken(l, "%", TOK_MODULO); break;
        case '^': return createToken(l, "^", TOK_EXPONENT); break;
        case '<': return createToken(l, "<", TOK_OP_LT); break;
        case '>': return createToken(l, ">", TOK_OP_GT); break;
        case '+': return createToken(l, "+", TOK_PLUS); break;
        case '-': return createToken(l, "-", TOK_MINUS); break;
        case '*': return createToken(l, "*", TOK_MULTIPLY); break;
        case '/': return createToken(l, "/", TOK_DIVISION); break;
        
        case '\0':
            token.type = TOK_EOF;
            token.lexeme[0] = '\0';

            return token;
        break;
    }

    token.type = TOK_ERROR;
    token.isError = true;
    snprintf(token.message, sizeof(token.message), "Invalid character: %c", l->current);

    return token;
}