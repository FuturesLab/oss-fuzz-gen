#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "janet.h"

#define MAX_CAPACITY 1024

static void initialize_env(JanetTable *env) {
    janet_table_init_raw(env, 10);
}

static void cleanup_env(JanetTable *env) {
    // Implement necessary cleanup if required
}

static void fuzz_janet_dobytes(const uint8_t *Data, size_t Size) {
    JanetTable env;
    initialize_env(&env);

    Janet out;
    janet_dobytes(&env, Data, (int32_t)Size, "./dummy_file", &out);

    cleanup_env(&env);
}

static void fuzz_janet_table_init_raw(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;

    int32_t capacity;
    memcpy(&capacity, Data, sizeof(int32_t));
    if (capacity < 0 || capacity > MAX_CAPACITY) return;

    JanetTable table;
    janet_table_init_raw(&table, capacity);
}

static void fuzz_janet_env_lookup(const uint8_t *Data, size_t Size) {
    JanetTable env;
    initialize_env(&env);

    JanetTable *new_env = janet_env_lookup(&env);

    cleanup_env(&env);
    // Assume new_env doesn't need cleanup
}

static void fuzz_janet_core_env(const uint8_t *Data, size_t Size) {
    JanetTable replacements;
    initialize_env(&replacements);

    JanetTable *core_env = janet_core_env(&replacements);

    cleanup_env(&replacements);
    // Assume core_env doesn't need cleanup
}

static void fuzz_janet_core_lookup_table(const uint8_t *Data, size_t Size) {
    JanetTable replacements;
    initialize_env(&replacements);

    JanetTable *lookup_table = janet_core_lookup_table(&replacements);

    cleanup_env(&replacements);
    // Assume lookup_table doesn't need cleanup
}

static void fuzz_janet_def(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;

    JanetTable env;
    initialize_env(&env);

    const char *name = "fuzz_var";
    Janet val;
    memcpy(&val, Data, sizeof(Janet));

    janet_def(&env, name, val, "Fuzz variable");

    cleanup_env(&env);
}

int LLVMFuzzerTestOneInput_979(const uint8_t *Data, size_t Size) {
    janet_init();

    fuzz_janet_dobytes(Data, Size);
    fuzz_janet_table_init_raw(Data, Size);
    fuzz_janet_env_lookup(Data, Size);
    fuzz_janet_core_env(Data, Size);
    fuzz_janet_core_lookup_table(Data, Size);
    fuzz_janet_def(Data, Size);

    janet_deinit();
    return 0;
}