// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_table at janet.c:33121:13 in janet.h
// janet_cstring at string.c:88:16 in janet.h
// janet_cstring at string.c:88:16 in janet.h
// janet_table_put at janet.c:33237:6 in janet.h
// janet_cfuns at janet.c:34239:6 in janet.h
// janet_cstring at string.c:88:16 in janet.h
// janet_table_get_ex at janet.c:33200:7 in janet.h
// janet_env_lookup at marsh.c:130:13 in janet.h
// janet_cfuns_ext at janet.c:34249:6 in janet.h
// janet_core_lookup_table at janet.c:8037:13 in janet.h
// janet_cfuns_prefix at janet.c:34259:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

static void initialize_janet_environment() {
    janet_init();
}

static void cleanup_janet_environment() {
    janet_deinit();
}

static JanetTable *create_dummy_table() {
    JanetTable *table = janet_table(0);
    Janet key = janet_cstringv("dummy_key");
    Janet value = janet_cstringv("dummy_value");
    janet_table_put(table, key, value);
    return table;
}

static void fuzz_janet_cfuns(JanetTable *env) {
    const JanetReg cfuns[] = {
        {NULL, NULL, NULL} // Terminating entry
    };
    janet_cfuns(env, "fuzz_", cfuns);
}

static void fuzz_janet_table_get_ex(JanetTable *env) {
    JanetTable *which = NULL;
    Janet key = janet_cstringv("dummy_key");
    janet_table_get_ex(env, key, &which);
}

static void fuzz_janet_env_lookup(JanetTable *env) {
    JanetTable *new_env = janet_env_lookup(env);
    // Assuming janet_env_lookup does not require manual deinitialization of the returned table
}

static void fuzz_janet_cfuns_ext(JanetTable *env) {
    const JanetRegExt cfuns_ext[] = {
        {NULL, NULL, NULL, NULL, 0} // Terminating entry
    };
    janet_cfuns_ext(env, "fuzz_ext_", cfuns_ext);
}

static void fuzz_janet_core_lookup_table(JanetTable *replacements) {
    JanetTable *lookup_table = janet_core_lookup_table(replacements);
    // Assuming janet_core_lookup_table does not require manual deinitialization of the returned table
}

static void fuzz_janet_cfuns_prefix(JanetTable *env) {
    const JanetReg cfuns[] = {
        {NULL, NULL, NULL} // Terminating entry
    };
    janet_cfuns_prefix(env, "fuzz_prefix_", cfuns);
}

int LLVMFuzzerTestOneInput_484(const uint8_t *Data, size_t Size) {
    initialize_janet_environment();

    JanetTable *dummy_table = create_dummy_table();

    if (Size > 0) {
        fuzz_janet_cfuns(dummy_table);
        fuzz_janet_table_get_ex(dummy_table);
        fuzz_janet_env_lookup(dummy_table);
        fuzz_janet_cfuns_ext(dummy_table);
        fuzz_janet_core_lookup_table(dummy_table);
        fuzz_janet_cfuns_prefix(dummy_table);
    }

    // Remove manual deinitialization of dummy_table to avoid double-free
    cleanup_janet_environment();
    return 0;
}