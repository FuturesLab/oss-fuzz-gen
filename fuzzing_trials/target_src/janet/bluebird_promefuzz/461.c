#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

static Janet random_janet_value(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) {
        return (Janet){.u64 = 0};
    }
    Janet value;
    memcpy(&value, Data, sizeof(Janet));
    return value;
}

static const char *random_string(const uint8_t *Data, size_t Size) {
    static char buffer[256];
    if (Size < 2) {
        buffer[0] = '\0';
        return buffer;
    }
    size_t len = Data[0] % 255;
    len = len < (Size - 1) ? len : (Size - 1);
    memcpy(buffer, Data + 1, len);
    buffer[len] = '\0';
    return buffer;
}

int LLVMFuzzerTestOneInput_461(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    janet_init(); // Initialize the Janet VM

    const char *name = random_string(Data, Size);
    Janet value = random_janet_value(Data, Size);

    // Test janet_dyn
    Janet result_dyn = janet_dyn(name);

    // Test janet_var_sm
    JanetTable *env = janet_table(0);
    janet_var_sm(env, name, value, "doc", "source_file", 1);

    // Test janet_var
    janet_var(env, name, value, "documentation");

    // Test janet_setdyn
    janet_setdyn(name, value);

    // Test janet_resolve_core
    Janet result_resolve_core = janet_resolve_core(name);

    janet_deinit(); // Deinitialize the Janet VM

    return 0;
}