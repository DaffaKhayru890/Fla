#include "../../include/symbol_table.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

ScopeNode *init_scope(char *name, int level, ScopeNode *parent) {
    ScopeNode *scope_node = (ScopeNode*)malloc(sizeof(ScopeNode));

    if(scope_node == NULL) {
        fprintf(stderr, "Error: can not init scope node\n");
        exit(EXIT_FAILURE);
    }
    
    scope_node->name = strdup(name);
    if(scope_node->name == NULL) {
        fprintf(stderr, "Error: scope node name not must null\n");
        exit(EXIT_FAILURE);
    }

    scope_node->level = level;
    scope_node->parent = NULL;
    scope_node->symbol_table = create_symbol_table(scope_node, 5);

    return scope_node;
}

SymbolTable *create_symbol_table(ScopeNode *scope, int capacity) {
    SymbolTable *symbol_table = (SymbolTable*)malloc(sizeof(SymbolTable));

    if(symbol_table == NULL) {
        fprintf(stderr, "Error: can not init symbol table\n");
        exit(EXIT_FAILURE);
    }

    symbol_table->capacity = capacity;
    symbol_table->symbol = (Symbol**)malloc(sizeof(Symbol*) * symbol_table->capacity);
    symbol_table->count = 0;

    if(symbol_table->symbol == NULL) {
        fprintf(stderr, "Error: can not create symbol table\n");
        exit(EXIT_FAILURE);
    }

    return symbol_table;
}

Symbol *create_symbol(SymbolTable *symbol_table, char *identifier, DataType data_type, SymbolKind symbol_kind) {
    Symbol *symbol = (Symbol*)malloc(sizeof(Symbol));

    if(symbol == NULL) {
        fprintf(stderr, "Error: can not init symbol\n");
        exit(EXIT_FAILURE);
    }

    symbol->identifier = strdup(identifier);
    if(symbol->identifier == NULL) {
        fprintf(stderr, "Error: symbol identifier must not be null\n");
        exit(EXIT_FAILURE);
    }

    symbol->data_type = data_type;
    symbol->symbol_kind = symbol_kind;

    return symbol;
}

Symbol *lookup_symbol(SymbolTable *symbol_table, char *identifier) {
    for(int i = 0; i < symbol_table->count; i++) {
        if(strcmp(symbol_table->symbol[i]->identifier, identifier) == 0) {
            return symbol_table->symbol[i];
        }
    }
    
    return NULL;
}

Symbol *lookup_nested_symbol(ScopeNode *scope, char *identifier) {
    if(scope == NULL || identifier == NULL) {
        return NULL;
    }

    Symbol *find_symbol = lookup_symbol(scope->symbol_table, identifier);
    if(find_symbol != NULL) {
        return NULL;
    }

    if(scope->parent != NULL) {
        return lookup_nested_symbol(scope->parent, identifier);
    }

    return NULL;
}

void add_symbol(SymbolTable *symbol_table, Symbol *new_symbol) {
    if(symbol_table == NULL || new_symbol == NULL) {
        fprintf(stderr, "Error: symbol table and symbol must not be null\n");
        exit(EXIT_FAILURE);
    }
    
    if(symbol_table->count >= symbol_table->capacity) {
        symbol_table->symbol = realloc(
            symbol_table->symbol,
            sizeof(Symbol*) * (symbol_table->capacity * 2)
        );

        if(symbol_table->symbol == NULL) {
            fprintf(stderr, "Error: failed to grow symbol table\n");
            exit(EXIT_FAILURE);
        }

        symbol_table->capacity = symbol_table->capacity * 2;
    }

    symbol_table->symbol[symbol_table->count] = new_symbol; 
    symbol_table->count++;
}
