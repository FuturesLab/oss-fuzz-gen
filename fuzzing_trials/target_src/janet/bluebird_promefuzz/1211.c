#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

static void initialize_janet(void) {
    janet_init();
}

static JanetTable *initialize_table(void) {
    return janet_core_env(NULL);
}

static void fuzz_janet_var_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    const char *name = "fuzz_var";
    Janet val = { .u64 = 0 };
    const char *documentation = "Fuzz variable";
    const char *source_file = "./dummy_file";
    int32_t source_line = 42;

    janet_var_sm(env, name, val, documentation, source_file, source_line);
}

static void fuzz_janet_def_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    const char *name = "fuzz_def";
    Janet val = { .u64 = 0 };
    const char *documentation = "Fuzz definition";
    const char *source_file = "./dummy_file";
    int32_t source_line = 42;

    janet_def_sm(env, name, val, documentation, source_file, source_line);
}

static void fuzz_janet_cfuns_ext(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetRegExt)) return;

    const char *regprefix = "fuzz";
    JanetRegExt cfuns[] = {
        { "fuzz_cfun", NULL, NULL, 0 },
        { NULL, NULL, NULL, 0 }
    };

    janet_cfuns_ext(env, regprefix, cfuns);
}

static void fuzz_janet_env_lookup_into(JanetTable *renv, JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    const char *prefix = "fuzz_";
    int recurse = 1;

    janet_env_lookup_into(renv, env, prefix, recurse);
}

static void fuzz_janet_cfuns_ext_prefix(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetRegExt)) return;

    const char *regprefix = "fuzz";
    JanetRegExt cfuns[] = {
        { "fuzz_cfun", NULL, NULL, 0 },
        { NULL, NULL, NULL, 0 }
    };

    janet_cfuns_ext_prefix(env, regprefix, cfuns);
}

int LLVMFuzzerTestOneInput_1211(const uint8_t *Data, size_t Size) {
    initialize_janet();

    JanetTable *env = initialize_table();
    JanetTable *renv = initialize_table();

    fuzz_janet_var_sm(env, Data, Size);
    fuzz_janet_def_sm(env, Data, Size);
    fuzz_janet_cfuns_ext(env, Data, Size);
    fuzz_janet_env_lookup_into(renv, env, Data, Size);
    fuzz_janet_cfuns_ext_prefix(env, Data, Size);

    janet_deinit();

    return 0;
}