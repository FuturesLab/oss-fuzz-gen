#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "janet.h"

static void initialize_janet_table(JanetTable *table) {
    memset(table, 0, sizeof(JanetTable));
    table->capacity = 0;
    table->count = 0;
    table->deleted = 0;
    table->data = NULL;
    table->proto = NULL;
}

int LLVMFuzzerTestOneInput_770(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet VM
    janet_init();

    JanetTable *env = janet_table(0);

    const char *name = "test_var";
    const char *documentation = "A test variable";
    Janet value;
    value.i64 = 42;

    janet_var(env, name, value, documentation);

    const char *code = "(+ 1 2)";
    Janet out;
    janet_dostring(env, code, "./dummy_file", &out);

    const char *source_file = "dummy.janet";
    int32_t source_line = 1;
    janet_def_sm(env, name, value, documentation, source_file, source_line);

    janet_setdyn(name, value);

    Janet resolved = janet_resolve_core(name);

    janet_def(env, name, value, documentation);

    // Cleanup Janet VM
    janet_deinit();

    return 0;
}