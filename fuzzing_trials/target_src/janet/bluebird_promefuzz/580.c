#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void initialize_janet() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

static JanetTable *create_dummy_table() {
    JanetTable *table = janet_table(10);
    Janet key = janet_cstringv("dummy_key");
    Janet value = janet_cstringv("dummy_value");
    janet_table_put(table, key, value);
    return table;
}

static Janet create_dummy_janet() {
    return janet_cstringv("dummy_key");
}

int LLVMFuzzerTestOneInput_580(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet
    initialize_janet();

    // Prepare dummy table and key
    JanetTable *table = create_dummy_table();
    Janet key = create_dummy_janet();

    // Fuzz janet_table_get_ex
    JanetTable *which = NULL;
    Janet result = janet_table_get_ex(table, key, &which);

    // Fuzz janet_core_env
    JanetTable *env = janet_core_env(table);

    // Fuzz janet_wrap_table
    Janet wrapped = janet_wrap_table(table);

    // Fuzz janet_table_get
    Janet get_result = janet_table_get(table, key);

    // Fuzz janet_core_lookup_table
    JanetTable *lookup_table = janet_core_lookup_table(table);

    // Fuzz janet_table_clear
    janet_table_clear(table);

    // Cleanup
    free(table);

    return 0;
}