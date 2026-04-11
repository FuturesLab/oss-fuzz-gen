// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_optuinteger64 at janet.c:4886:10 in janet.h
// janet_equals at value.c:249:5 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_getinteger at janet.c:4630:9 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "janet.h"

static void fuzz_janet_optuinteger64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t) + sizeof(int32_t) * 2) return;
    uint64_t dflt = *((uint64_t *)Data);
    Data += sizeof(uint64_t);
    int32_t argc = *((int32_t *)Data);
    Data += sizeof(int32_t);
    int32_t n = *((int32_t *)Data);
    Data += sizeof(int32_t);

    Janet *argv = (Janet *)malloc(argc * sizeof(Janet));
    if (argv == NULL) return;

    for (int32_t i = 0; i < argc; i++) {
        argv[i].u64 = (i < (int32_t)(Size - sizeof(uint64_t) * (i + 1))) ? *((uint64_t *)(Data + sizeof(uint64_t) * i)) : 0;
    }

    volatile uint64_t result = janet_optuinteger64(argv, argc, n, dflt);

    free(argv);
}

static void fuzz_janet_equals(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 2) return;
    Janet x = *((Janet *)Data);
    Janet y = *((Janet *)(Data + sizeof(Janet)));

    volatile int result = janet_equals(x, y);
}

static void fuzz_janet_unwrap_integer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x = *((Janet *)Data);

    volatile int32_t result = janet_unwrap_integer(x);
}

static void fuzz_janet_checktype(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + sizeof(JanetType)) return;
    Janet x = *((Janet *)Data);
    JanetType type = *((JanetType *)(Data + sizeof(Janet)));

    volatile int result = janet_checktype(x, type);
}

static void fuzz_janet_wrap_integer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t x = *((int32_t *)Data);

    volatile Janet result = janet_wrap_integer(x);
}

static void fuzz_janet_getinteger(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) + sizeof(Janet)) return;
    int32_t n = *((int32_t *)Data);
    Data += sizeof(int32_t);
    Janet *argv = (Janet *)malloc(n * sizeof(Janet));
    if (argv == NULL) return;

    for (int32_t i = 0; i < n; i++) {
        argv[i].i64 = (i < (int32_t)(Size - sizeof(int64_t) * (i + 1))) ? *((int64_t *)(Data + sizeof(int64_t) * i)) : 0;
    }

    if (n >= 0 && n < (int32_t)(Size / sizeof(Janet))) {
        volatile int32_t result = janet_getinteger(argv, n);
    }

    free(argv);
}

int LLVMFuzzerTestOneInput_331(const uint8_t *Data, size_t Size) {
    fuzz_janet_optuinteger64(Data, Size);
    fuzz_janet_equals(Data, Size);
    fuzz_janet_unwrap_integer(Data, Size);
    fuzz_janet_checktype(Data, Size);
    fuzz_janet_wrap_integer(Data, Size);
    fuzz_janet_getinteger(Data, Size);

    return 0;
}