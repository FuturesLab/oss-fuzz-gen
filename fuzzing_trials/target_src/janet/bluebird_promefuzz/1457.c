#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static JanetTable *create_dummy_table() {
    JanetTable *table = janet_table(10);
    for (int i = 0; i < 5; i++) {
        Janet key = janet_wrap_integer(i);
        Janet value = janet_wrap_integer(i * 10);
        janet_table_put(table, key, value);
    }
    return table;
}

static JanetStruct create_dummy_struct() {
    static JanetKV kvs[5];
    for (int i = 0; i < 5; i++) {
        kvs[i].key = janet_wrap_integer(i + 5);
        kvs[i].value = janet_wrap_integer((i + 5) * 10);
    }
    return kvs;
}

int LLVMFuzzerTestOneInput_1457(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return 0;

    // Initialize Janet runtime
    janet_init();

    JanetTable *table = create_dummy_table();
    JanetStruct jstruct = create_dummy_struct();

    // Fuzz janet_table_merge_struct
    janet_table_merge_struct(table, jstruct);

    // Fuzz janet_table_clone
    JanetTable *cloned_table = janet_table_clone(table);

    // Fuzz janet_table_find
    Janet key = janet_wrap_integer(Data[0] % 10);
    janet_table_find(table, key);

    // Fuzz janet_struct_to_table
    JanetTable *struct_to_table = janet_struct_to_table(jstruct);

    // Fuzz janet_table_to_struct
    janet_table_to_struct(table);

    // Cleanup
    // Note: Do not deinit or free cloned_table and struct_to_table as they are GC managed

    // Deinitialize Janet runtime
    janet_deinit();

    return 0;
}