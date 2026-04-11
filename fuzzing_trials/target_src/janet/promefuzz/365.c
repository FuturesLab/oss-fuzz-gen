// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_cfuns at janet.c:34239:6 in janet.h
// janet_table_merge_table at janet.c:33313:6 in janet.h
// janet_var at janet.c:34118:6 in janet.h
// janet_def_sm at janet.c:34099:6 in janet.h
// janet_dostring at run.c:139:5 in janet.h
// janet_cfuns_prefix at janet.c:34259:6 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_table at janet.c:33121:13 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>

static JanetTable* create_dummy_table() {
    JanetTable *table = janet_table(0);
    return table;
}

static void fuzz_janet_cfuns(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetReg)) return;
    const JanetReg *cfuns = (const JanetReg *)Data;
    janet_cfuns(env, "fuzz_prefix", cfuns);
}

static void fuzz_janet_table_merge_table(JanetTable *table, const uint8_t *Data, size_t Size) {
    JanetTable *other = create_dummy_table();
    janet_table_merge_table(table, other);
}

static void fuzz_janet_var(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet val = *(const Janet *)Data;
    janet_var(env, "fuzz_var", val, "Fuzz documentation");
}

static void fuzz_janet_def_sm(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet val = *(const Janet *)Data;
    janet_def_sm(env, "fuzz_symbol", val, "Fuzz doc", "fuzz_file", 42);
}

static void fuzz_janet_dostring(JanetTable *env, const uint8_t *Data, size_t Size) {
    char *code = (char *)malloc(Size + 1);
    memcpy(code, Data, Size);
    code[Size] = '\0';
    Janet out;
    janet_dostring(env, code, "fuzz_source", &out);
    free(code);
}

static void fuzz_janet_cfuns_prefix(JanetTable *env, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetReg)) return;
    const JanetReg *cfuns = (const JanetReg *)Data;
    janet_cfuns_prefix(env, "fuzz_prefix", cfuns);
}

int LLVMFuzzerTestOneInput_365(const uint8_t *Data, size_t Size) {
    janet_init(); // Initialize Janet VM

    JanetTable *env = create_dummy_table();

    fuzz_janet_cfuns(env, Data, Size);
    fuzz_janet_table_merge_table(env, Data, Size);
    fuzz_janet_var(env, Data, Size);
    fuzz_janet_def_sm(env, Data, Size);
    fuzz_janet_dostring(env, Data, Size);
    fuzz_janet_cfuns_prefix(env, Data, Size);

    janet_deinit(); // Deinitialize Janet VM
    return 0;
}