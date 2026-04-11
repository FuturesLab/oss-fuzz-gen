// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_table_weakv at janet.c:33131:13 in janet.h
// janet_table_init_raw at janet.c:33106:13 in janet.h
// janet_table_init_raw at janet.c:33106:13 in janet.h
// janet_table_merge_table at janet.c:33313:6 in janet.h
// janet_table_init_raw at janet.c:33106:13 in janet.h
// janet_table_init_raw at janet.c:33106:13 in janet.h
// janet_dostring at run.c:139:5 in janet.h
// janet_opttable at janet.c:4539:1 in janet.h
// janet_gettable at janet.c:4514:1 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

#define MAX_CAPACITY 1024

static void initialize_janet() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

static void fuzz_janet_table_weakv(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(const int32_t *)Data;
    JanetTable *table = janet_table_weakv(capacity);
    // Perform any operations on the table if necessary
}

static void fuzz_janet_table_merge_table(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(int32_t)) return;
    int32_t capacity1 = *(const int32_t *)Data;
    int32_t capacity2 = *(const int32_t *)(Data + sizeof(int32_t));

    JanetTable table1, table2;
    janet_table_init_raw(&table1, capacity1);
    janet_table_init_raw(&table2, capacity2);

    janet_table_merge_table(&table1, &table2);
    // Cleanup if necessary
}

static void fuzz_janet_table_init_raw(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(const int32_t *)Data;
    if (capacity < 0 || capacity > MAX_CAPACITY) return;

    JanetTable table;
    janet_table_init_raw(&table, capacity);
    // Perform operations on the table if necessary
}

static void fuzz_janet_dostring(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;
    char *code = malloc(Size + 1);
    if (!code) return;

    memcpy(code, Data, Size);
    code[Size] = '\0'; // Ensure null-terminated

    JanetTable env;
    janet_table_init_raw(&env, 0);
    Janet out;
    janet_dostring(&env, code, "./dummy_file", &out);

    free(code);
}

static void fuzz_janet_opttable(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 3) return;
    int32_t argc = *(const int32_t *)Data;
    int32_t n = *(const int32_t *)(Data + sizeof(int32_t));
    int32_t dflt_len = *(const int32_t *)(Data + 2 * sizeof(int32_t));
    
    if (argc < 0) return;

    Janet *argv = malloc(sizeof(Janet) * argc);
    if (!argv) return;

    for (int32_t i = 0; i < argc; i++) {
        argv[i].u64 = (uint64_t)Data[i % Size];
    }

    JanetTable *table = janet_opttable(argv, argc, n, dflt_len);
    // Perform operations on the table if necessary

    free(argv);
}

static void fuzz_janet_gettable(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) + sizeof(Janet)) return;
    int32_t index = *(const int32_t *)Data;
    int32_t argc = (Size - sizeof(int32_t)) / sizeof(Janet);
    
    if (index < 0 || index >= argc) return;

    Janet *argv = (Janet *)(Data + sizeof(int32_t));
    JanetTable *table = janet_gettable(argv, index);
    // Perform operations on the table if necessary
}

int LLVMFuzzerTestOneInput_381(const uint8_t *Data, size_t Size) {
    initialize_janet();
    fuzz_janet_table_weakv(Data, Size);
    fuzz_janet_table_merge_table(Data, Size);
    fuzz_janet_table_init_raw(Data, Size);
    fuzz_janet_dostring(Data, Size);
    fuzz_janet_opttable(Data, Size);
    fuzz_janet_gettable(Data, Size);
    return 0;
}