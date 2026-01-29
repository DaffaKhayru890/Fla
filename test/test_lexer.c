#include "../include/utils.h"
#include "../include/lexer.h"
#include "stdio.h"

int main() {
    char *list_tokens[] = {
        "TK_KEYWORD",
        "TK_IDENTIFIER",
        "TK_STRING",
        "TK_NUMBER",
        "TK_LPAREN",
        "TK_RPAREN",
        "TK_RARROW",
        "TK_SEMICOLON",
        "TK_COLON",
        "TK_ASSIGN",
        "TK_EMPTY",
        "TK_EOF"
    };

    char *source_code = read_file("../example/function.vla");

    Lexer *lexer = init_lexer(source_code);
    Token *token = init_token();

    do{
        tokenize(lexer, token);

        printf("type: %s, literal: %-10s (%d,%d)\n", token->type[list_tokens], token->literal ,lexer->line, lexer->column);
    }while(token->type != TK_EOF);

    free_lexer(lexer, token);

    return 0;
}