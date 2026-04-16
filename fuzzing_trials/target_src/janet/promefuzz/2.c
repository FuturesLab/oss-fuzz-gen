// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_tuple_end at tuple.c:44:14 in janet.h
// janet_opttuple at janet.c:4527:1 in janet.h
// janet_length at value.c:641:9 in janet.h
// janet_tuple_begin at tuple.c:34:8 in janet.h
// janet_tuple_n at tuple.c:50:14 in janet.h
// janet_gettuple at janet.c:4513:1 in janet.h
// janet_init at vm.c:1652:5 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_tuple_end(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 2) return;
    Janet *tuple = (Janet *)malloc(sizeof(Janet) * 2);
    if (!tuple) return;
    memcpy(tuple, Data, sizeof(Janet) * 2);
    janet_tuple_end(tuple);
    free(tuple);
}

static void fuzz_janet_opttuple(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 2 + sizeof(int32_t) * 2) return;
    const Janet *argv = (const Janet *)Data;
    int32_t argc = *((int32_t *)(Data + sizeof(Janet)));
    int32_t n = *((int32_t *)(Data + sizeof(Janet) + sizeof(int32_t)));
    JanetTuple dflt = (JanetTuple)(Data + sizeof(Janet) + sizeof(int32_t) * 2);
    janet_opttuple(argv, argc, n, dflt);
}

static void fuzz_janet_length(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x = *((Janet *)Data);
    janet_length(x);
}

static void fuzz_janet_tuple_begin(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t length = *((int32_t *)Data);
    if (length >= 0) {
        janet_tuple_begin(length);
    }
}

static void fuzz_janet_tuple_n(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) + sizeof(Janet)) return;
    int32_t n = *((int32_t *)Data);
    const Janet *values = (const Janet *)(Data + sizeof(int32_t));
    janet_tuple_n(values, n);
}

static void fuzz_janet_gettuple(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + sizeof(int32_t)) return;
    const Janet *argv = (const Janet *)Data;
    int32_t n = *((int32_t *)(Data + sizeof(Janet)));
    janet_gettuple(argv, n);
}

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    static int initialized = 0;
    if (!initialized) {
        janet_init(); // Initialize the Janet VM before use
        initialized = 1;
    }
    fuzz_janet_tuple_end(Data, Size);
    fuzz_janet_opttuple(Data, Size);
    fuzz_janet_length(Data, Size);
    fuzz_janet_tuple_begin(Data, Size);
    fuzz_janet_tuple_n(Data, Size);
    fuzz_janet_gettuple(Data, Size);
    return 0;
}