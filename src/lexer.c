#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "./lexer.h"

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

static void advanced(Lexer *l) {
    if(!isAtEnd(l)) {
        if(l->current == '\n') {
            l->line++;
            l->col = 0;
        }else {
            l->col = 0;
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
        while(peek(l) != '\n') {
            advanced(l);
        }
    }
}

static Token createToken(Lexer *l, char *lexeme ,TokenType type) {
    Token token;

    strcpy(token.lexeme, lexeme);
    token.type = type;

    return token;
}

static Token scanTwoChars(Lexer *l, char first, char second) {
    Token token;
    
    if(peek(l) == first && peekNext(l) == second && peekNext != '\0') {
        token.lexeme[0] = first;
        token.lexeme[1] = second;

        

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

static Token scanDigit(Lexer *l) {
    if(isAtEnd(l)) {
        Token token;

        token.lexeme[0] = '\0';
        token.type = TOK_EOF;

        return token;
    }

    Token token;

    int posLexeme = 0;

    while(isdigit(peek(l)) && posLexeme < MAX_LITERAL - 1) {
        token.lexeme[posLexeme] = l->current;

        advanced(l);

        posLexeme++;
    }

    token.lexeme[posLexeme] = '\0';

    token.type = TOK_INT;
    
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

    skipWhitespace(l);
    skipComment(l);

    if(isalpha(peek(l))) {
        return scanKeyword(l);
    }

    if(isdigit(peek(l))) {
        return scanDigit(l);
    }

    char ch = l->current;
    advanced(l);

    switch(ch) {
        case '(': return createToken(l, "(", TOK_LPAREN);
        case ')': return createToken(l, ")", TOK_RPAREN);
        case '{': return createToken(l, "{", TOK_LBRACE);
        case '}': return createToken(l, "}", TOK_RBRACE);
        case '[': return createToken(l, "[", TOK_LBRACKETS);
        case ']': return createToken(l, "]", TOK_RBRACKETS);
        case ',': return createToken(l, "(", TOK_COMMA);
        case ':': return createToken(l, ":", TOK_COLON);
        case ';': return createToken(l, ";", TOK_SEMICOLON);
        case '?': return createToken(l, "?", TOK_OP_UNARY);

        break;
    }
}