// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_table at janet.c:33121:13 in janet.h
// janet_cstring at string.c:88:16 in janet.h
// janet_cstring at string.c:88:16 in janet.h
// janet_table_put at janet.c:33237:6 in janet.h
// janet_cstring at string.c:88:16 in janet.h
// janet_table_get_ex at janet.c:33200:7 in janet.h
// janet_core_env at janet.c:7992:13 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_table_get at janet.c:33179:7 in janet.h
// janet_core_lookup_table at janet.c:8037:13 in janet.h
// janet_table_clear at janet.c:33278:6 in janet.h
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

int LLVMFuzzerTestOneInput_753(const uint8_t *Data, size_t Size) {
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