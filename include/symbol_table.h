#pragma once 

#include "stdbool.h"

typedef enum {
    SYMBOL_FUNCTION,
}SymbolKind;

typedef enum {
    TYPE_INT
}DataType;

typedef enum {
    SCOPE_GLOBAL
}Scope;

typedef struct {
    SymbolKind symbol_kind;
    DataType data_type;
    char *identifier;
    Scope scope;
}Symbol;

typedef struct {
    Symbol **symbol;
    int symbol_capacity;
    int symbol_count;
}SymbolTable;

SymbolTable *init_symbol_table(int capacity);
Symbol *create_symbol(SymbolTable *symbol_table, char *identifier, DataType data_type, SymbolKind symbol_kind, Scope scope);

void add_symbol(SymbolTable *symbol_table, Symbol *new_symbol);