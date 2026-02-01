#pragma once 

#include "stdbool.h"

typedef struct ScopeNode ScopeNode;

typedef enum {
    SYMBOL_FUNCTION,
    SYMBOL_VARIABLE,
}SymbolKind;

typedef enum {
    TYPE_INT
}DataType;

typedef struct {
    SymbolKind symbol_kind;
    DataType data_type;
    char *identifier;
}Symbol;

typedef struct {
    Symbol **symbol;
    int capacity;
    int count;
}SymbolTable;

struct ScopeNode {
    char *name;
    int level;
    SymbolTable *symbol_table;
    ScopeNode *parent;
};

ScopeNode *create_scope(char *name, int level, ScopeNode *parent);
SymbolTable *create_symbol_table(ScopeNode *scope, int capacity);
Symbol *create_symbol(SymbolTable *symbol_table, char *identifier, DataType data_type, SymbolKind symbol_kind);
Symbol *lookup_symbol(SymbolTable *symbol_table, char *identifier);
Symbol *lookup_nested_symbol(ScopeNode *scope, char *identifier);

void add_symbol(SymbolTable *symbol_table, Symbol *new_symbol);

void free_scope(ScopeNode *scope);
void free_nested_scope(ScopeNode *scope);
void free_symbol_table(SymbolTable *symbol_table);
void free_symbol(Symbol *symbol);