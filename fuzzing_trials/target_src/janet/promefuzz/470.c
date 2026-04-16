// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_table_weakv at janet.c:33131:13 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_table_weakk at janet.c:33126:13 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_table_init_raw at janet.c:33106:13 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_core_lookup_table at janet.c:8037:13 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_table_clear at janet.c:33278:6 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_table_init_raw at janet.c:33106:13 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

static void fuzz_janet_table_weakv(int32_t capacity) {
    JanetTable *table = janet_table_weakv(capacity);
    if (table) {
        janet_table_deinit(table);
    }
}

static void fuzz_janet_table_weakk(int32_t capacity) {
    JanetTable *table = janet_table_weakk(capacity);
    if (table) {
        janet_table_deinit(table);
    }
}

static void fuzz_janet_table_init_raw(JanetTable *table, int32_t capacity) {
    JanetTable *initialized_table = janet_table_init_raw(table, capacity);
    if (initialized_table) {
        janet_table_deinit(initialized_table);
    }
}

static void fuzz_janet_core_lookup_table(JanetTable *replacements) {
    JanetTable *table = janet_core_lookup_table(replacements);
    if (table) {
        janet_table_deinit(table);
    }
}

static void fuzz_janet_table_clear(JanetTable *table) {
    janet_table_clear(table);
}

int LLVMFuzzerTestOneInput_470(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    int32_t capacity = *((int32_t *)Data);
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    // Initialize a dummy Janet environment
    janet_init();

    // Fuzz janet_table_weakv
    fuzz_janet_table_weakv(capacity);

    // Fuzz janet_table_weakk
    fuzz_janet_table_weakk(capacity);

    // Prepare a JanetTable for other functions
    JanetTable table;
    janet_table_init_raw(&table, capacity);

    // Fuzz janet_table_init_raw
    fuzz_janet_table_init_raw(&table, capacity);

    // Fuzz janet_core_lookup_table
    fuzz_janet_core_lookup_table(&table);

    // Fuzz janet_table_clear
    fuzz_janet_table_clear(&table);

    // Cleanup
    janet_table_deinit(&table);
    janet_deinit();

    return 0;
}