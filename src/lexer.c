#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "./lexer.h"

// =============================== Helper Function ===============================

static bool isAtEnd(Lexer *l) {
    return l->input[l->pos] == '\0';
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

static Token createToken(Lexer *l, TokenType type) {
    Token token;

    token.type = type;

    return token;
}

static Token scanKeyword(Lexer *l) {
    Token token;
    
    if(isAtEnd(l)) {
        token.lexeme[0] = '\0';
        token.type = TOK_EOF;

        return token;
    }

    int posLexeme = 0;

    while((isalnum(peek(l)) || peek(l) == '_') && !isAtEnd(l) && posLexeme < MAX_LITERAL - 1) {
        token.lexeme[posLexeme] = l->current;

        advanced(l);
        
        posLexeme++;
    }

    token.lexeme[posLexeme] = '\0';

    if(strcmp(token.lexeme, "use") == 0) return createToken(l, TOK_KEY_USE);
    if(strcmp(token.lexeme, "fun") == 0) return createToken(l, TOK_KEY_FUN);
    if(strcmp(token.lexeme, "if") == 0) return createToken(l, TOK_KEY_IF);
    if(strcmp(token.lexeme, "else") == 0) return createToken(l, TOK_KEY_ELSE);
    if(strcmp(token.lexeme, "break") == 0) return createToken(l, TOK_KEY_BREAK);
    if(strcmp(token.lexeme, "continue") == 0) return createToken(l, TOK_KEY_CONTINUE);
    if(strcmp(token.lexeme, "while") == 0) return createToken(l, TOK_KEY_WHILE);
    if(strcmp(token.lexeme, "for") == 0) return createToken(l, TOK_KEY_FOR);
    if(strcmp(token.lexeme, "switch") == 0) return createToken(l, TOK_KEY_SWITCH);
    if(strcmp(token.lexeme, "true") == 0) return createToken(l, TOK_KEY_TRUE);
    if(strcmp(token.lexeme, "false") == 0) return createToken(l, TOK_KEY_FALSE);

    token.type = TOK_IDENTIFIER;

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
}