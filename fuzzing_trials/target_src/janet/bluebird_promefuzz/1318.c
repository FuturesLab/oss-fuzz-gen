#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

#define MAX_CAPACITY 1024

static void fuzz_janet_dobytes(const uint8_t *Data, size_t Size) {
    JanetTable env;
    janet_table_init_raw(&env, 10);

    Janet out;
    janet_dobytes(&env, Data, (int32_t)Size, "fuzz_source", &out);
}

static void fuzz_janet_table_init_raw(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) {
        return;
    }

    int32_t capacity;
    memcpy(&capacity, Data, sizeof(int32_t));
    capacity = capacity < 0 ? 0 : (capacity > MAX_CAPACITY ? MAX_CAPACITY : capacity);

    JanetTable table;
    janet_table_init_raw(&table, capacity);
}

static void fuzz_janet_env_lookup(const uint8_t *Data, size_t Size) {
    JanetTable env;
    janet_table_init_raw(&env, 10);

    JanetTable *new_env = janet_env_lookup(&env);
    (void)new_env; // Suppress unused variable warning
}

static void fuzz_janet_core_env(const uint8_t *Data, size_t Size) {
    JanetTable replacements;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of janet_table_init_raw
    janet_table_init_raw(&replacements, JANET_SANDBOX_FS_TEMP);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    JanetTable *core_env = janet_core_env(NULL);
    JanetTable *custom_env = janet_core_env(&replacements);
    (void)core_env;
    (void)custom_env;
}

static void fuzz_janet_core_lookup_table(const uint8_t *Data, size_t Size) {
    JanetTable replacements;
    janet_table_init_raw(&replacements, 10);

    JanetTable *lookup_table = janet_core_lookup_table(NULL);
    JanetTable *custom_lookup_table = janet_core_lookup_table(&replacements);
    (void)lookup_table;
    (void)custom_lookup_table;
}

static void fuzz_janet_def(const uint8_t *Data, size_t Size) {
    JanetTable env;
    janet_table_init_raw(&env, 10);

    const char *name = "fuzz_var";
    Janet val;
    val.u64 = 0;

    janet_def(&env, name, val, "Fuzz variable documentation");
}

int LLVMFuzzerTestOneInput_1318(const uint8_t *Data, size_t Size) {
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