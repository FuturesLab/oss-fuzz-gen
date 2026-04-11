#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void initialize_janet_table(JanetTable *table) {
    table->gc.flags = 0;
    table->gc.data.next = NULL;
    table->count = 0;
    table->capacity = 2; // Ensure capacity is non-zero for valid operations
    table->deleted = 0;
    table->data = (JanetKV *)calloc(table->capacity, sizeof(JanetKV));
    table->proto = NULL;
}

int LLVMFuzzerTestOneInput_437(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet VM
    janet_init();

    JanetTable env;
    initialize_janet_table(&env);

    // Fuzz janet_dyn
    char name[256];
    size_t name_len = Size < 255 ? Size : 255;
    memcpy(name, Data, name_len);
    name[name_len] = '\0';
    janet_dyn(name);

    // Fuzz janet_var_sm
    Janet val;
    val.u64 = 0; // Initialize with a default value
    janet_var_sm(&env, name, val, "documentation", "source_file", 42);

    // Fuzz janet_var
    janet_var(&env, name, val, "documentation");

    // Fuzz janet_table_find
    Janet key;
    key.u64 = 0; // Ensure key is initialized
    JanetKV *kv = janet_table_find(&env, key);
    if (kv) {
        // Handle found key-value pair
    }

    // Fuzz janet_setdyn
    janet_setdyn(name, val);

    // Fuzz janet_resolve_core
    janet_resolve_core(name);

    // Free allocated memory for JanetTable
    free(env.data);

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}