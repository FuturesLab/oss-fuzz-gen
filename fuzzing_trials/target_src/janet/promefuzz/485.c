// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_table_init at janet.c:33101:13 in janet.h
// janet_table_get_ex at janet.c:33200:7 in janet.h
// janet_dictionary_next at janet.c:34030:16 in janet.h
// janet_dictionary_view at janet.c:34506:5 in janet.h
// janet_dictionary_get at janet.c:34021:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static JanetTable *init_table(int32_t capacity) {
    JanetTable *table = (JanetTable *)malloc(sizeof(JanetTable));
    if (table) {
        janet_table_init(table, capacity);
    }
    return table;
}

static void cleanup_table(JanetTable *table) {
    if (table) {
        free(table);
    }
}

static void fuzz_janet_table_init(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity;
    memcpy(&capacity, Data, sizeof(int32_t));
    JanetTable *table = init_table(capacity);
    cleanup_table(table);
}

static void fuzz_janet_table_get_ex(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    JanetTable *table = init_table(10);
    Janet key;
    memcpy(&key, Data, sizeof(Janet));
    JanetTable *which = NULL;
    janet_table_get_ex(table, key, &which);
    cleanup_table(table);
}

static void fuzz_janet_dictionary_next(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetKV) * 2) return;
    JanetKV *kvs = (JanetKV *)malloc(sizeof(JanetKV) * 10);
    if (!kvs) return;
    memcpy(kvs, Data, sizeof(JanetKV) * 2);
    const JanetKV *next = janet_dictionary_next(kvs, 10, NULL);
    free(kvs);
}

static void fuzz_janet_dictionary_view(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    JanetTable *table = init_table(10);
    Janet tab;
    memcpy(&tab, Data, sizeof(Janet));
    const JanetKV *data;
    int32_t len, cap;
    janet_dictionary_view(tab, &data, &len, &cap);
    cleanup_table(table);
}

static void fuzz_janet_dictionary_get(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    JanetKV *kvs = (JanetKV *)malloc(sizeof(JanetKV) * 10);
    if (!kvs) return;
    memcpy(kvs, Data, sizeof(JanetKV));
    Janet key;
    memcpy(&key, Data, sizeof(Janet));
    janet_dictionary_get(kvs, 10, key);
    free(kvs);
}

int LLVMFuzzerTestOneInput_485(const uint8_t *Data, size_t Size) {
    fuzz_janet_table_init(Data, Size);
    fuzz_janet_table_get_ex(Data, Size);
    fuzz_janet_dictionary_next(Data, Size);
    fuzz_janet_dictionary_view(Data, Size);
    fuzz_janet_dictionary_get(Data, Size);
    return 0;
}