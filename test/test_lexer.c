#include "../include/helper.h"
#include "../include/lexer.h"
#include "stdio.h"

int main() {
    char *list_tokens[] = {
        "TK_KEYWORD",
        "TK_IDENTIFIER",
        "TK_NUMBER",
        "TK_LPAREN",
        "TK_RPAREN",
        "TK_LBRACE",
        "TK_RBRACE",
        "TK_SEMICOLON",
        "TK_EMPTY",
        "TK_EOF"
    };

    char *source_code = read_file("../example/example.c");

    Lexer *lexer = init_lexer(source_code);
    Token *token = init_token();

    do{
        tokenize(lexer, token);

        printf("type: %s, literal: %s\n", token->type[list_tokens], token->literal);
        printf("line: %d, column: %d\n\n", lexer->line, lexer->column);
    }while(token->type != TK_EOF);

    free_lexer(lexer, token);

    return 0;
}