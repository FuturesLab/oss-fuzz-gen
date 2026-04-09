// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_table_init at janet.c:33101:13 in janet.h
// janet_table_merge_table at janet.c:33313:6 in janet.h
// janet_env_lookup at marsh.c:130:13 in janet.h
// janet_core_env at janet.c:7992:13 in janet.h
// janet_env_lookup_into at marsh.c:104:6 in janet.h
// janet_table at janet.c:33121:13 in janet.h
// janet_init at vm.c:1652:5 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

static void fuzz_janet_table_init(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(const int32_t *)Data;
    JanetTable table;
    janet_table_init(&table, capacity);
}

static void fuzz_janet_table_merge_table(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(JanetTable)) return;
    const JanetTable *table1 = (const JanetTable *)(Data);
    const JanetTable *table2 = (const JanetTable *)(Data + sizeof(JanetTable));
    janet_table_merge_table((JanetTable *)table1, (JanetTable *)table2);
}

static void fuzz_janet_env_lookup(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetTable)) return;
    const JanetTable *env = (const JanetTable *)Data;
    JanetTable *new_env = janet_env_lookup((JanetTable *)env);
    // Clean up if necessary
    if (new_env) {
        // Assuming a function to clean up the table
    }
}

static void fuzz_janet_core_env(const uint8_t *Data, size_t Size) {
    JanetTable *replacements = NULL;
    if (Size >= sizeof(JanetTable)) {
        replacements = (JanetTable *)Data;
    }
    JanetTable *env = janet_core_env(replacements);
    // Clean up if necessary
    if (env) {
        // Assuming a function to clean up the table
    }
}

static void fuzz_janet_env_lookup_into(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(JanetTable) + sizeof(int)) return;
    JanetTable *renv = (JanetTable *)Data;
    JanetTable *env = (JanetTable *)(Data + sizeof(JanetTable));
    const char *prefix = NULL;
    int recurse = *(int *)(Data + 2 * sizeof(JanetTable));
    janet_env_lookup_into(renv, env, prefix, recurse);
}

static void fuzz_janet_table(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(const int32_t *)Data;
    JanetTable *table = janet_table(capacity);
    // Clean up if necessary
    if (table) {
        // Assuming a function to clean up the table
    }
}

int LLVMFuzzerTestOneInput_338(const uint8_t *Data, size_t Size) {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
    fuzz_janet_table_init(Data, Size);
    fuzz_janet_table_merge_table(Data, Size);
    fuzz_janet_env_lookup(Data, Size);
    fuzz_janet_core_env(Data, Size);
    fuzz_janet_env_lookup_into(Data, Size);
    fuzz_janet_table(Data, Size);
    return 0;
}