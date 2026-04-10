// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_table_init at janet.c:33101:13 in janet.h
// janet_table_init at janet.c:33101:13 in janet.h
// janet_resolve_ext at janet.c:34439:14 in janet.h
// janet_table_clone at janet.c:33287:13 in janet.h
// janet_table_merge_table at janet.c:33313:6 in janet.h
// janet_table_init_raw at janet.c:33106:13 in janet.h
// janet_env_lookup at marsh.c:130:13 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

static void initialize_janet_vm() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

static JanetTable *initialize_table(int32_t capacity) {
    JanetTable *table = (JanetTable *)malloc(sizeof(JanetTable));
    if (table) {
        janet_table_init(table, capacity);
    }
    return table;
}

static JanetSymbol generate_symbol(const uint8_t *Data, size_t Size) {
    return (JanetSymbol)(Data[0] % 256); // Simplified symbol generation
}

static void fuzz_janet_table_init(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(int32_t *)Data;
    JanetTable table;
    janet_table_init(&table, capacity);
}

static void fuzz_janet_resolve_ext(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetSymbol)) return;
    JanetTable *table = initialize_table(10);
    JanetSymbol sym = generate_symbol(Data, Size);
    janet_resolve_ext(table, sym);
    free(table);
}

static void fuzz_janet_table_clone(const uint8_t *Data, size_t Size) {
    JanetTable *table = initialize_table(10);
    if (table) {
        JanetTable *cloned_table = janet_table_clone(table);
        (void)cloned_table; // Use cloned_table if needed
        free(table);
    }
}

static void fuzz_janet_table_merge_table(const uint8_t *Data, size_t Size) {
    JanetTable *table1 = initialize_table(10);
    JanetTable *table2 = initialize_table(5);
    if (table1 && table2) {
        janet_table_merge_table(table1, table2);
        free(table1);
        free(table2);
    }
}

static void fuzz_janet_table_init_raw(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(int32_t *)Data;
    JanetTable table;
    janet_table_init_raw(&table, capacity);
}

static void fuzz_janet_env_lookup(const uint8_t *Data, size_t Size) {
    JanetTable *env = initialize_table(10);
    if (env) {
        JanetTable *new_env = janet_env_lookup(env);
        (void)new_env; // Use new_env if needed
        free(env);
    }
}

int LLVMFuzzerTestOneInput_317(const uint8_t *Data, size_t Size) {
    initialize_janet_vm();
    fuzz_janet_table_init(Data, Size);
    fuzz_janet_resolve_ext(Data, Size);
    fuzz_janet_table_clone(Data, Size);
    fuzz_janet_table_merge_table(Data, Size);
    fuzz_janet_table_init_raw(Data, Size);
    fuzz_janet_env_lookup(Data, Size);
    return 0;
}