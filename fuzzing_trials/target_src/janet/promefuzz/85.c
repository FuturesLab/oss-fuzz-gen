// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_cfuns at janet.c:34239:6 in janet.h
// janet_table_get_ex at janet.c:33200:7 in janet.h
// janet_env_lookup at marsh.c:130:13 in janet.h
// janet_cfuns_ext at janet.c:34249:6 in janet.h
// janet_core_lookup_table at janet.c:8037:13 in janet.h
// janet_cfuns_prefix at janet.c:34259:6 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>

static void fuzz_janet_cfuns(JanetTable *env, const char *regprefix, const JanetReg *cfuns) {
    if (cfuns && cfuns->name) {
        janet_cfuns(env, regprefix, cfuns);
    }
}

static void fuzz_janet_table_get_ex(JanetTable *t, Janet key, JanetTable **which) {
    if (t) {
        Janet value = janet_table_get_ex(t, key, which);
        (void)value; // Suppress unused variable warning
    }
}

static void fuzz_janet_env_lookup(JanetTable *env) {
    if (env) {
        JanetTable *new_env = janet_env_lookup(env);
        (void)new_env; // Suppress unused variable warning
    }
}

static void fuzz_janet_cfuns_ext(JanetTable *env, const char *regprefix, const JanetRegExt *cfuns) {
    if (cfuns && cfuns->name) {
        janet_cfuns_ext(env, regprefix, cfuns);
    }
}

static void fuzz_janet_core_lookup_table(JanetTable *replacements) {
    if (replacements) {
        JanetTable *table = janet_core_lookup_table(replacements);
        (void)table; // Suppress unused variable warning
    }
}

static void fuzz_janet_cfuns_prefix(JanetTable *env, const char *regprefix, const JanetReg *cfuns) {
    if (cfuns && cfuns->name) {
        janet_cfuns_prefix(env, regprefix, cfuns);
    }
}

int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetTable) + sizeof(JanetReg) + sizeof(JanetRegExt)) {
        return 0;
    }

    // Initialize Janet environment
    janet_init();

    // Prepare environment and data
    JanetTable *env = (JanetTable *)Data;
    
    // Ensure null-terminated strings for regprefix
    const char *regprefix = (const char *)(Data + sizeof(JanetTable));
    size_t regprefix_length = strnlen(regprefix, Size - sizeof(JanetTable));
    if (regprefix_length == Size - sizeof(JanetTable)) {
        return 0; // Not null-terminated
    }
    char *safe_regprefix = (char *)malloc(regprefix_length + 1);
    if (!safe_regprefix) {
        janet_deinit();
        return 0; // Memory allocation failed
    }
    memcpy(safe_regprefix, regprefix, regprefix_length);
    safe_regprefix[regprefix_length] = '\0';

    const JanetReg *cfuns = (const JanetReg *)(Data + sizeof(JanetTable) + sizeof(const char *));
    const JanetRegExt *cfuns_ext = (const JanetRegExt *)(Data + sizeof(JanetTable) + sizeof(const char *) + sizeof(JanetReg));

    // Fuzz janet_cfuns
    fuzz_janet_cfuns(env, safe_regprefix, cfuns);

    // Fuzz janet_table_get_ex
    Janet key;
    key.u64 = *(uint64_t *)(Data + sizeof(JanetTable) + sizeof(const char *) + sizeof(JanetReg) + sizeof(JanetRegExt));
    JanetTable *which = NULL;
    fuzz_janet_table_get_ex(env, key, &which);

    // Fuzz janet_env_lookup
    fuzz_janet_env_lookup(env);

    // Fuzz janet_cfuns_ext
    fuzz_janet_cfuns_ext(env, safe_regprefix, cfuns_ext);

    // Fuzz janet_core_lookup_table
    fuzz_janet_core_lookup_table(env);

    // Fuzz janet_cfuns_prefix
    fuzz_janet_cfuns_prefix(env, safe_regprefix, cfuns);

    // Cleanup
    free(safe_regprefix);
    janet_deinit();

    return 0;
}