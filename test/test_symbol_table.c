#include "../include/symbol_table.h"

#include "stdio.h"
#include "./unity.h"
#include "./unity_internals.h"

void setUp(void) {}
void tearDown(void) {}

void test_scope_node() {
    ScopeNode *global = create_scope("angka", 0, NULL);

    TEST_ASSERT_EQUAL_STRING("angka", global->name);
    TEST_ASSERT_EQUAL_PTR(NULL, global->parent);
    TEST_ASSERT_EQUAL_INT(0, global->level);

    free_scope(global);
}

void test_symbol_table() {
    ScopeNode *global = create_scope("angka", 0, NULL);
    SymbolTable *table = create_symbol_table(global, 2);

    TEST_ASSERT_EQUAL_STRING("angka", global->name);
    TEST_ASSERT_EQUAL_PTR(NULL, global->parent);
    TEST_ASSERT_EQUAL_INT(0, global->level);

    TEST_ASSERT_EQUAL_INT(2, table->capacity);

    free_symbol_table(table);
    free_scope(global);
}

void test_symbol() {
    ScopeNode *global = create_scope("angka", 0, NULL);
    SymbolTable *table = create_symbol_table(global, 2);

    Symbol *angka = create_symbol(table, "angka", TYPE_INT, SYMBOL_VARIABLE);
    add_symbol(table, angka);

    TEST_ASSERT_EQUAL_STRING("angka", global->name);
    TEST_ASSERT_EQUAL_PTR(NULL, global->parent);
    TEST_ASSERT_EQUAL_INT(0, global->level);

    TEST_ASSERT_EQUAL_INT(2, table->capacity);
    TEST_ASSERT_EQUAL_PTR(angka, table->symbol[0]);

    TEST_ASSERT_EQUAL_STRING("angka", angka->identifier);
    TEST_ASSERT_EQUAL(TYPE_INT, angka->data_type);
    TEST_ASSERT_EQUAL(SYMBOL_VARIABLE, angka->symbol_kind);


    free_symbol(angka);
    free_symbol_table(table);
    free_scope(global);
}

void test_nested_scope_node() {
    ScopeNode *global = create_scope("angka", 0, NULL);
    ScopeNode *function = create_scope("main", 1, global);

    TEST_ASSERT_EQUAL_STRING("angka", global->name);
    TEST_ASSERT_EQUAL_PTR(NULL, global->parent);
    TEST_ASSERT_EQUAL_INT(0, global->level);

    TEST_ASSERT_EQUAL_STRING("main", function->name);
    TEST_ASSERT_EQUAL_PTR(global, function->parent);
    TEST_ASSERT_EQUAL_INT(1, function->level);

    free_nested_scope(global);
}

void test_lookup_symbol() {
    ScopeNode *global = create_scope("angka", 0, NULL);
    SymbolTable *table = create_symbol_table(global, 2);

    Symbol *angka = create_symbol(table, "angka", TYPE_INT, SYMBOL_VARIABLE);
    add_symbol(table, angka);

    TEST_ASSERT_EQUAL_STRING("angka", global->name);
    TEST_ASSERT_EQUAL_PTR(NULL, global->parent);
    TEST_ASSERT_EQUAL_INT(0, global->level);

    TEST_ASSERT_EQUAL_INT(2, table->capacity);
    TEST_ASSERT_EQUAL_PTR(angka, table->symbol[0]);

    TEST_ASSERT_EQUAL_STRING("angka", angka->identifier);
    TEST_ASSERT_EQUAL(TYPE_INT, angka->data_type);
    TEST_ASSERT_EQUAL(SYMBOL_VARIABLE, angka->symbol_kind);

    Symbol *find_symbol = lookup_symbol(table, "angka");

    TEST_ASSERT_EQUAL_STRING("angka", find_symbol->identifier);
    TEST_ASSERT_EQUAL(TYPE_INT, find_symbol->data_type);
    TEST_ASSERT_EQUAL(SYMBOL_VARIABLE, find_symbol->symbol_kind);

    free_symbol(angka);
    free_symbol_table(table);
    free_scope(global);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_scope_node);
    RUN_TEST(test_symbol_table);
    RUN_TEST(test_symbol);
    RUN_TEST(test_nested_scope_node);
    RUN_TEST(test_lookup_symbol);

    return UNITY_END();
}