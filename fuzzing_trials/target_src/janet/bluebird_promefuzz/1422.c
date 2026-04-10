#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void initialize_janet_table(JanetTable *table) {
    table->count = 0;
    table->capacity = 8; // Arbitrary initial capacity
    table->deleted = 0;
    table->data = (JanetKV *)malloc(sizeof(JanetKV) * table->capacity);
    memset(table->data, 0, sizeof(JanetKV) * table->capacity);
    table->proto = NULL;
}

static void cleanup_janet_table(JanetTable *table) {
    free(table->data);
}

int LLVMFuzzerTestOneInput_1422(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize the Janet VM
    janet_init();

    // Prepare a null-terminated string for the name
    char name[256];
    size_t name_len = (Size < 255) ? Size : 255;
    memcpy(name, Data, name_len);
    name[name_len] = '\0';

    // Prepare a Janet value
    Janet value;
    value.u64 = 0; // Initialize to zero

    // Prepare JanetTable
    JanetTable env;
    initialize_janet_table(&env);

    // Fuzz janet_dyn
    Janet result_dyn = janet_dyn(name);

    // Fuzz janet_var
    janet_var(&env, name, value, "documentation");

    // Fuzz janet_var_sm
    janet_var_sm(&env, name, value, "documentation", "./dummy_file", 42);

    // Fuzz janet_table_find
    JanetKV *kv = janet_table_find(&env, value);

    // Fuzz janet_setdyn
    janet_setdyn(name, value);

    // Fuzz janet_resolve_core
    Janet result_resolve_core = janet_resolve_core(name);

    // Cleanup
    cleanup_janet_table(&env);

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}