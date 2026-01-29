#include "../include/symbol_table.h"

#include "stdio.h"

void print_symbol_table(SymbolTable *symbol_table) {
    printf("=================== Symbol Table ===================\n\n");
    printf("%-20s %-15s %-15s %-10s\n", "identifier", "type", "kind", "scope");

    for(int i = 0; i < symbol_table->symbol_count; i++) {
        Symbol *symbol = symbol_table->symbol[i];

        char *data_type;
        switch(symbol->data_type){
            case TYPE_INT: 
                data_type = "int";
            break;
        }

        char *symbol_kind;
        switch(symbol->symbol_kind){
            case SYMBOL_FUNCTION: 
                symbol_kind = "function";
            break;
        }

        char *scope;
        switch(symbol->scope){
            case SCOPE_GLOBAL: 
                scope = "global";
            break;
        }

        printf("%-20s %-15s %-15s %-10s\n", symbol->identifier, data_type, symbol_kind, scope);
    }

    printf("\n\n");
}

int main() {
    SymbolTable *symbol_table = init_symbol_table(3);
    Symbol *symbol_first = create_symbol(symbol_table, "main", TYPE_INT, SYMBOL_FUNCTION, SCOPE_GLOBAL);
    Symbol *symbol_second = create_symbol(symbol_table, "baru", TYPE_INT, SYMBOL_FUNCTION, SCOPE_GLOBAL);
    add_symbol(symbol_table, symbol_first);
    add_symbol(symbol_table, symbol_second);

    print_symbol_table(symbol_table);

    return 0;
}