#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

static JanetTable *initialize_table(void) {
    janet_init(); // Initialize the Janet VM
    JanetTable *table = janet_table(0);
    return table;
}

static void fuzz_janet_var_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure there's enough data for a string and a uint64_t
    size_t name_len = Data[0] % (Size - 9); // Ensure name length is within bounds
    const char *name = (const char *)(Data + 1);
    Janet val = { .u64 = *(uint64_t *)(Data + 1 + name_len) };
    const char *documentation = "fuzz documentation";
    const char *source_file = "./dummy_file";
    int32_t source_line = 42;

    // Ensure the name is null-terminated
    char *name_cpy = (char *)malloc(name_len + 1);
    if (!name_cpy) return;
    memcpy(name_cpy, name, name_len);
    name_cpy[name_len] = '\0';

    janet_var_sm(env, name_cpy, val, documentation, source_file, source_line);

    free(name_cpy);
}

static void fuzz_janet_dobytes(JanetTable *env, const uint8_t *Data, size_t Size) {
    Janet out;
    janet_dobytes(env, Data, (int32_t)Size, "./dummy_file", &out);
}

static void fuzz_janet_var(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure there's enough data for a string and a uint64_t
    size_t name_len = Data[0] % (Size - 9); // Ensure name length is within bounds
    const char *name = (const char *)(Data + 1);
    Janet val = { .u64 = *(uint64_t *)(Data + 1 + name_len) };
    const char *documentation = "fuzz documentation";

    // Ensure the name is null-terminated
    char *name_cpy = (char *)malloc(name_len + 1);
    if (!name_cpy) return;
    memcpy(name_cpy, name, name_len);
    name_cpy[name_len] = '\0';

    janet_var(env, name_cpy, val, documentation);

    free(name_cpy);
}

static void fuzz_janet_def_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure there's enough data for a string and a uint64_t
    size_t name_len = Data[0] % (Size - 9); // Ensure name length is within bounds
    const char *name = (const char *)(Data + 1);
    Janet val = { .u64 = *(uint64_t *)(Data + 1 + name_len) };
    const char *documentation = "fuzz documentation";
    const char *source_file = "./dummy_file";
    int32_t source_line = 42;

    // Ensure the name is null-terminated
    char *name_cpy = (char *)malloc(name_len + 1);
    if (!name_cpy) return;
    memcpy(name_cpy, name, name_len);
    name_cpy[name_len] = '\0';

    janet_def_sm(env, name_cpy, val, documentation, source_file, source_line);

    free(name_cpy);
}

static void fuzz_janet_dostring(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    
    // Ensure the input string is null-terminated
    char *str = (char *)malloc(Size + 1);
    if (!str) return;
    memcpy(str, Data, Size);
    str[Size] = '\0';

    Janet out;
    janet_dostring(env, str, "./dummy_file", &out);

    free(str); // Free the allocated memory
}

static void fuzz_janet_def(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure there's enough data for a string and a uint64_t
    size_t name_len = Data[0] % (Size - 9); // Ensure name length is within bounds
    const char *name = (const char *)(Data + 1);
    Janet val = { .u64 = *(uint64_t *)(Data + 1 + name_len) };
    const char *documentation = "fuzz documentation";

    // Ensure the name is null-terminated
    char *name_cpy = (char *)malloc(name_len + 1);
    if (!name_cpy) return;
    memcpy(name_cpy, name, name_len);
    name_cpy[name_len] = '\0';

    janet_def(env, name_cpy, val, documentation);

    free(name_cpy);
}

int LLVMFuzzerTestOneInput_960(const uint8_t *Data, size_t Size) {
    JanetTable *env = initialize_table();

    fuzz_janet_var_sm(env, Data, Size);
    fuzz_janet_dobytes(env, Data, Size);
    fuzz_janet_var(env, Data, Size);
    fuzz_janet_def_sm(env, Data, Size);
    fuzz_janet_dostring(env, Data, Size);
    fuzz_janet_def(env, Data, Size);

    janet_deinit(); // Properly deinitialize the Janet VM
    return 0;
}