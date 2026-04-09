#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void initialize_janet_table(JanetTable *table) {
    table->gc.flags = 0;
    table->gc.data.next = NULL;
    table->count = 0;
    table->capacity = 0;
    table->deleted = 0;
    table->data = NULL;
    table->proto = NULL;
}

static JanetTable *create_janet_table(void) {
    JanetTable *table = janet_table(0);
    return table;
}

int LLVMFuzzerTestOneInput_163(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet environment
    janet_init();

    // Properly create JanetTable using Janet API
    JanetTable *env = create_janet_table();

    // Fuzz janet_var_sm
    const char *var_name_sm = "fuzz_var_sm";
    Janet var_val_sm = { .u64 = 0 };
    const char *doc_sm = "fuzz doc sm";
    const char *source_file_sm = "./dummy_file_sm";
    int32_t source_line_sm = 42;

    janet_var_sm(env, var_name_sm, var_val_sm, doc_sm, source_file_sm, source_line_sm);

    // Fuzz janet_dobytes
    Janet out_dobytes;
    janet_dobytes(env, Data, (int32_t)Size, "./dummy_file_dobytes", &out_dobytes);

    // Fuzz janet_var
    const char *var_name = "fuzz_var";
    Janet var_val = { .u64 = 1 };
    const char *doc = "fuzz doc";
    janet_var(env, var_name, var_val, doc);

    // Fuzz janet_dostring
    Janet out_dostring;
    const char *source_str = "fuzz_string";
    janet_dostring(env, source_str, "./dummy_file_dostring", &out_dostring);

    // Fuzz janet_def_sm
    const char *def_name_sm = "fuzz_def_sm";
    Janet def_val_sm = { .u64 = 2 };
    const char *def_doc_sm = "fuzz def doc sm";
    const char *def_source_file_sm = "./dummy_file_def_sm";
    int32_t def_source_line_sm = 84;

    janet_def_sm(env, def_name_sm, def_val_sm, def_doc_sm, def_source_file_sm, def_source_line_sm);

    // Fuzz janet_env_lookup_into
    JanetTable *renv = create_janet_table();
    const char *prefix = "fuzz_prefix";
    int recurse = 1;

    janet_env_lookup_into(renv, env, prefix, recurse);

    // Cleanup Janet environment
    janet_deinit();

    return 0;
}