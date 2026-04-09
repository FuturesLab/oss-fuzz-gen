// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_table at janet.c:33121:13 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_var_sm at janet.c:34110:6 in janet.h
// janet_dobytes at run.c:31:5 in janet.h
// janet_def_sm at janet.c:34099:6 in janet.h
// janet_dostring at run.c:139:5 in janet.h
// janet_env_lookup_into at marsh.c:104:6 in janet.h
// janet_def at janet.c:34105:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>

static void initialize_janet_environment(JanetTable *env) {
    /* Initialize the Janet VM before using any Janet functions */
    janet_init();
    /* Create a new JanetTable with initial capacity */
    *env = *janet_table(10);
}

static void cleanup_janet_environment() {
    /* Clean up the Janet VM after use */
    janet_deinit();
}

static void fuzz_janet_var_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return; // Ensure there's at least one byte for the name
    char *name = strndup((const char *)Data, Size);
    Janet val;
    val.u64 = 0; // Initialize Janet value
    janet_var_sm(env, name, val, NULL, NULL, 0);
    free(name);
}

static void fuzz_janet_dobytes(JanetTable *env, const uint8_t *Data, size_t Size) {
    Janet out;
    janet_dobytes(env, Data, (int32_t)Size, "./dummy_file", &out);
}

static void fuzz_janet_def_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return; // Ensure there's at least one byte for the name
    char *name = strndup((const char *)Data, Size);
    Janet val;
    val.u64 = 0; // Initialize Janet value
    janet_def_sm(env, name, val, NULL, NULL, 0);
    free(name);
}

static void fuzz_janet_dostring(JanetTable *env, const uint8_t *Data, size_t Size) {
    char *str = strndup((const char *)Data, Size);
    Janet out;
    janet_dostring(env, str, "./dummy_file", &out);
    free(str);
}

static void fuzz_janet_env_lookup_into(JanetTable *renv, JanetTable *env, const uint8_t *Data, size_t Size) {
    char *prefix = strndup((const char *)Data, Size);
    janet_env_lookup_into(renv, env, prefix, 1);
    free(prefix);
}

static void fuzz_janet_def(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) return; // Ensure there's at least one byte for the name
    char *name = strndup((const char *)Data, Size);
    Janet val;
    val.u64 = 0; // Initialize Janet value
    janet_def(env, name, val, NULL);
    free(name);
}

int LLVMFuzzerTestOneInput_278(const uint8_t *Data, size_t Size) {
    JanetTable env;
    JanetTable renv;
    initialize_janet_environment(&env);
    initialize_janet_environment(&renv);
    
    fuzz_janet_var_sm(&env, Data, Size);
    fuzz_janet_dobytes(&env, Data, Size);
    fuzz_janet_def_sm(&env, Data, Size);
    fuzz_janet_dostring(&env, Data, Size);
    fuzz_janet_env_lookup_into(&renv, &env, Data, Size);
    fuzz_janet_def(&env, Data, Size);

    cleanup_janet_environment();
    return 0;
}