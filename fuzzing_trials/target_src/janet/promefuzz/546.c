// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_deinit at vm.c:1732:6 in janet.h
// janet_init at vm.c:1652:5 in janet.h
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
#include <string.h>
#include "janet.h"

static void initialize_janet() {
    janet_init();
}

static JanetTable *initialize_janet_table() {
    return janet_core_env(NULL);
}

static void fuzz_janet_var_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    size_t name_len = strnlen((const char *)Data, Size);
    char *name = (char *)malloc(name_len + 1);
    if (!name) return;
    memcpy(name, Data, name_len);
    name[name_len] = '\0';

    Janet val = { .u64 = 0 }; // Assuming a default value for simplicity
    const char *documentation = "Fuzzing janet_var_sm";
    const char *source_file = "./dummy_file";
    int32_t source_line = 1;
    janet_var_sm(env, name, val, documentation, source_file, source_line);

    free(name);
}

static void fuzz_janet_def_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    size_t name_len = strnlen((const char *)Data, Size);
    char *name = (char *)malloc(name_len + 1);
    if (!name) return;
    memcpy(name, Data, name_len);
    name[name_len] = '\0';

    Janet val = { .u64 = 0 }; // Assuming a default value for simplicity
    const char *documentation = "Fuzzing janet_def_sm";
    const char *source_file = "./dummy_file";
    int32_t source_line = 1;
    janet_def_sm(env, name, val, documentation, source_file, source_line);

    free(name);
}

static void fuzz_janet_cfuns_ext(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    size_t prefix_len = strnlen((const char *)Data, Size);
    char *regprefix = (char *)malloc(prefix_len + 1);
    if (!regprefix) return;
    memcpy(regprefix, Data, prefix_len);
    regprefix[prefix_len] = '\0';

    JanetRegExt cfuns[] = {
        { "fuzz_function", NULL, "Fuzzing janet_cfuns_ext", "./dummy_file", 1 },
        { NULL, NULL, NULL, NULL, 0 }
    };
    janet_cfuns_ext(env, regprefix, cfuns);

    free(regprefix);
}

static void fuzz_janet_env_lookup_into(JanetTable *renv, JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    size_t prefix_len = strnlen((const char *)Data, Size);
    char *prefix = (char *)malloc(prefix_len + 1);
    if (!prefix) return;
    memcpy(prefix, Data, prefix_len);
    prefix[prefix_len] = '\0';

    int recurse = 1;
    janet_env_lookup_into(renv, env, prefix, recurse);

    free(prefix);
}

static void fuzz_janet_cfuns_ext_prefix(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    size_t prefix_len = strnlen((const char *)Data, Size);
    char *regprefix = (char *)malloc(prefix_len + 1);
    if (!regprefix) return;
    memcpy(regprefix, Data, prefix_len);
    regprefix[prefix_len] = '\0';

    JanetRegExt cfuns[] = {
        { "fuzz_function_prefix", NULL, "Fuzzing janet_cfuns_ext_prefix", "./dummy_file", 1 },
        { NULL, NULL, NULL, NULL, 0 }
    };
    janet_cfuns_ext_prefix(env, regprefix, cfuns);

    free(regprefix);
}

int LLVMFuzzerTestOneInput_546(const uint8_t *Data, size_t Size) {
    initialize_janet();
    JanetTable *env = initialize_janet_table();
    JanetTable *renv = initialize_janet_table();

    fuzz_janet_var_sm(env, Data, Size);
    fuzz_janet_def_sm(env, Data, Size);
    fuzz_janet_cfuns_ext(env, Data, Size);
    fuzz_janet_env_lookup_into(renv, env, Data, Size);
    fuzz_janet_cfuns_ext_prefix(env, Data, Size);

    janet_deinit(); // Cleanup Janet environment

    return 0;
}