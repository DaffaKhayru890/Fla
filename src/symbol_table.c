#include "../include/symbol_table.h"

#include "stdlib.h"
#include "stdio.h"

SymbolTable *init_symbol_table(int capacity) {
    SymbolTable *symbol_table = (SymbolTable*)malloc(sizeof(SymbolTable));

    if(symbol_table == NULL) {
        perror("Failed initialized symbo table");
    }

    symbol_table->symbol_capacity = capacity;
    symbol_table->symbol = (Symbol**)malloc(sizeof(Symbol*) * symbol_table->symbol_capacity);
    symbol_table->symbol_count = 0;

    if(symbol_table->symbol == NULL) {
        perror("Failed to create symbol table");
    }

    return symbol_table;
}

Symbol *create_symbol(SymbolTable *symbol_table, char *identifier, DataType data_type, SymbolKind symbol_kind, Scope scope) {
    Symbol *symbol = (Symbol*)malloc(sizeof(Symbol));

    if(symbol == NULL) {
        perror("Failed initialized symbo table");
    }

    symbol->identifier = identifier;
    symbol->data_type = TYPE_INT;
    symbol->symbol_kind = SYMBOL_FUNCTION;
    symbol->scope = scope;

    return symbol;
}

void add_symbol(SymbolTable *symbol_table, Symbol *new_symbol) {
    if(symbol_table->symbol_count >= symbol_table->symbol_capacity) {
        perror("Symbol table is full");
    }

    symbol_table->symbol[symbol_table->symbol_count] = new_symbol; 
    symbol_table->symbol_count++;
}