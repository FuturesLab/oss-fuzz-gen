// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_core_env at janet.c:7992:13 in janet.h
// janet_var_sm at janet.c:34110:6 in janet.h
// janet_def_sm at janet.c:34099:6 in janet.h
// janet_cfuns_ext at janet.c:34249:6 in janet.h
// janet_env_lookup_into at marsh.c:104:6 in janet.h
// janet_cfuns_ext_prefix at janet.c:34272:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "janet.h"

static void initialize_janet() {
    janet_init();
}

static void cleanup_janet() {
    janet_deinit();
}

static JanetTable *initialize_table() {
    JanetTable *table = janet_core_env(NULL);
    return table;
}

static void fuzz_janet_var_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    size_t name_len = strnlen((const char *)Data, Size);
    char *name = (char *) malloc(name_len + 1);
    if (!name) return;
    memcpy(name, Data, name_len);
    name[name_len] = '\0';

    Janet val = { .u64 = 0 };
    const char *documentation = "doc";
    const char *source_file = "./dummy_file";
    int32_t source_line = 42;
    janet_var_sm(env, name, val, documentation, source_file, source_line);

    free(name);
}

static void fuzz_janet_def_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    size_t name_len = strnlen((const char *)Data, Size);
    char *name = (char *) malloc(name_len + 1);
    if (!name) return;
    memcpy(name, Data, name_len);
    name[name_len] = '\0';

    Janet val = { .u64 = 0 };
    const char *documentation = "doc";
    const char *source_file = "./dummy_file";
    int32_t source_line = 42;
    janet_def_sm(env, name, val, documentation, source_file, source_line);

    free(name);
}

static void fuzz_janet_cfuns_ext(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetRegExt)) return;
    const char *regprefix = "prefix";
    JanetRegExt cfuns[] = {
        { .name = (const char *)Data, .cfun = NULL, .documentation = "doc", .source_file = "./dummy_file", .source_line = 42 },
        { .name = NULL }
    };
    janet_cfuns_ext(env, regprefix, cfuns);
}

static void fuzz_janet_env_lookup_into(JanetTable *renv, JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    size_t prefix_len = strnlen((const char *)Data, Size);
    char *prefix = (char *) malloc(prefix_len + 1);
    if (!prefix) return;
    memcpy(prefix, Data, prefix_len);
    prefix[prefix_len] = '\0';
    int recurse = 1;
    janet_env_lookup_into(renv, env, prefix, recurse);
    free(prefix);
}

static void fuzz_janet_cfuns_ext_prefix(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetRegExt)) return;
    const char *regprefix = "prefix";
    JanetRegExt cfuns[] = {
        { .name = (const char *)Data, .cfun = NULL, .documentation = "doc", .source_file = "./dummy_file", .source_line = 42 },
        { .name = NULL }
    };
    janet_cfuns_ext_prefix(env, regprefix, cfuns);
}

int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size) {
    initialize_janet();
    
    JanetTable *env = initialize_table();
    if (!env) {
        cleanup_janet();
        return 0;
    }

    fuzz_janet_var_sm(env, Data, Size);
    fuzz_janet_def_sm(env, Data, Size);
    fuzz_janet_cfuns_ext(env, Data, Size);
    fuzz_janet_env_lookup_into(env, env, Data, Size);
    fuzz_janet_cfuns_ext_prefix(env, Data, Size);

    cleanup_janet();
    return 0;
}