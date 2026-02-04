#include "../../include/parser.h"

#include <stddef.h>
#include <string.h>

ASTNode *parseFuncDecl(Parser *p, Lexer *l) {
    ASTNode *parametersNode = NULL;
    ASTNode *funcDeclNode = NULL;

    eatToken(p, l, TOK_KEY_FUN);

    char *func_identifier;

    if(match(p, TOK_IDENTIFIER)) {
        strcpy(func_identifier, p->current.lexeme);
    }

    eatToken(p, l, TOK_LPAREN);

    while(p->current.type != TOK_RPAREN && p->current.type != TOK_EOF) {
        char *param_identifier;
        char *param_type;
        
        if(match(p, TOK_IDENTIFIER)) {
            strcpy(param_identifier, p->current.lexeme);
        }

        eatToken(p ,l ,TOK_IDENTIFIER);
        eatToken(p, l, TOK_COMMA);

        strcpy(param_type, p->current.lexeme);

        switch(p->current.type) {
            case TOK_TYPE_INT:
                eatToken(p, l, TOK_TYPE_INT);
            break; 

            case TOK_TYPE_DOUBLE:
                eatToken(p, l, TOK_TYPE_DOUBLE);
            break; 

            case TOK_TYPE_CHAR:
                eatToken(p, l, TOK_TYPE_CHAR);
            break; 

            case TOK_TYPE_STRING:
                eatToken(p, l, TOK_TYPE_STRING);
            break; 

            case TOK_TYPE_BOOLEAN:
                eatToken(p, l, TOK_TYPE_BOOLEAN);
            break; 
        }

        if(!parametersNode) {
            createParamNode(parametersNode, param_identifier, param_type);
        }

        
    }
}

ASTNode *parseReturn(Parser *p, Lexer *l);
ASTNode *parseBlock(Parser *p, Lexer *l);
ASTNode *parseVarDecl(Parser *p, Lexer *l);
ASTNode *parseIf(Parser *p, Lexer *l);
ASTNode *parseWhile(Parser *p, Lexer *l);
ASTNode *parseFor(Parser *p, Lexer *l);
ASTNode *parseSwitch(Parser *p, Lexer *l);