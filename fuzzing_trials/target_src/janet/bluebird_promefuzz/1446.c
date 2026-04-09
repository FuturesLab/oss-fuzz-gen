#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void initialize_janet_environment(JanetTable *env) {
    env->gc.flags = 0;
    env->gc.data.next = NULL;
    env->count = 0;
    env->capacity = 0;
    env->deleted = 0;
    env->data = NULL;
    env->proto = NULL;
}

static void ensure_janet_table_initialized(JanetTable *env) {
    if (env->capacity == 0) {
        env->capacity = 8;  // Set a default capacity
        env->data = malloc(sizeof(JanetKV) * env->capacity);
        memset(env->data, 0, sizeof(JanetKV) * env->capacity);
    }
}

static void fuzz_janet_var_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return;
    }
    ensure_janet_table_initialized(env);
    char *name = (char *)malloc(Size + 1);
    memcpy(name, Data, Size);
    name[Size] = '\0';
    Janet val = { .u64 = 0 };
    const char *documentation = "Documentation";
    const char *source_file = "source.janet";
    int32_t source_line = 42;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 5 of janet_var_sm
    janet_var_sm(env, name, val, documentation, source_file, JANET_STACKFRAME_TAILCALL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    free(name);
}

static void fuzz_janet_dobytes(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return;
    }
    ensure_janet_table_initialized(env);
    Janet out;
    janet_dobytes(env, Data, (int32_t)Size, "./dummy_file", &out);
}

static void fuzz_janet_var(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return;
    }
    ensure_janet_table_initialized(env);
    char *name = (char *)malloc(Size + 1);
    memcpy(name, Data, Size);
    name[Size] = '\0';
    Janet val = { .u64 = 0 };
    const char *documentation = "Documentation";
    janet_var(env, name, val, documentation);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_var to janet_table_put
    Janet ret_janet_resolve_core_jkled = janet_resolve_core((const char *)"r");
    JanetBuffer uqjcyyii;
    memset(&uqjcyyii, 0, sizeof(uqjcyyii));
    Janet ret_janet_wrap_buffer_quhup = janet_wrap_buffer(&uqjcyyii);

    janet_table_put(env, ret_janet_resolve_core_jkled, ret_janet_wrap_buffer_quhup);

    // End mutation: Producer.APPEND_MUTATOR

    free(name);
}

static void fuzz_janet_def_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return;
    }
    ensure_janet_table_initialized(env);
    char *name = (char *)malloc(Size + 1);
    memcpy(name, Data, Size);
    name[Size] = '\0';
    Janet val = { .u64 = 0 };
    const char *documentation = "Documentation";
    const char *source_file = "source.janet";
    int32_t source_line = 42;
    janet_def_sm(env, name, val, documentation, source_file, source_line);
    free(name);
}

static void fuzz_janet_dostring(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return;
    }
    ensure_janet_table_initialized(env);
    char *str = (char *)malloc(Size + 1);
    memcpy(str, Data, Size);
    str[Size] = '\0';
    Janet out;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of janet_dostring
    janet_dostring(env, (const char *)"w", "./dummy_file", &out);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    free(str);
}

static void fuzz_janet_def(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return;
    }
    ensure_janet_table_initialized(env);
    char *name = (char *)malloc(Size + 1);
    memcpy(name, Data, Size);
    name[Size] = '\0';
    Janet val = { .u64 = 0 };
    const char *documentation = "Documentation";
    janet_def(env, name, val, documentation);
    free(name);
}

int LLVMFuzzerTestOneInput_1446(const uint8_t *Data, size_t Size) {
    janet_init();
    JanetTable env;
    initialize_janet_environment(&env);

    fuzz_janet_var_sm(&env, Data, Size);
    fuzz_janet_dobytes(&env, Data, Size);
    fuzz_janet_var(&env, Data, Size);
    fuzz_janet_def_sm(&env, Data, Size);
    fuzz_janet_dostring(&env, Data, Size);
    fuzz_janet_def(&env, Data, Size);

    free(env.data);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function janet_deinit with janet_loop
    janet_loop();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    return 0;
}