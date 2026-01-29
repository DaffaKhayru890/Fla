#include "../include/symbol_table.h"

#include "stdio.h"

int main() {
    ScopeNode *global = init_scope("global", 0, NULL);
    ScopeNode *function = init_scope("main", 1, global);

    SymbolTable *table1 = create_symbol_table(global, 2);
    SymbolTable *table2 = create_symbol_table(function, 2);

    Symbol *angka = create_symbol(table2, "main", TYPE_INT, SYMBOL_VARIABLE);
    add_symbol(table1, angka);

    Symbol *main = create_symbol(table2, "main", TYPE_INT, SYMBOL_FUNCTION);
    add_symbol(table2, main);


    return 0;
}