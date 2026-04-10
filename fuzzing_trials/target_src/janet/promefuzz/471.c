// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_table_weakv at janet.c:33131:13 in janet.h
// janet_table_weakk at janet.c:33126:13 in janet.h
// janet_table_weakkv at janet.c:33136:13 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_sweep at gc.c:404:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

static int janet_initialized = 0;

static void initialize_janet() {
    if (!janet_initialized) {
        janet_init();
        janet_initialized = 1;
    }
}

static void cleanup_janet() {
    if (janet_initialized) {
        janet_deinit();
        janet_initialized = 0;
    }
}

static void fuzz_janet_table_weakv(int32_t capacity) {
    JanetTable *table = janet_table_weakv(capacity);
    // Do not deinitialize as it is managed by GC
}

static void fuzz_janet_table_weakk(int32_t capacity) {
    JanetTable *table = janet_table_weakk(capacity);
    // Do not deinitialize as it is managed by GC
}

static void fuzz_janet_table_weakkv(int32_t capacity) {
    JanetTable *table = janet_table_weakkv(capacity);
    // Do not deinitialize as it is managed by GC
}

static void fuzz_janet_gcpressure(size_t s) {
    janet_gcpressure(s);
}

int LLVMFuzzerTestOneInput_471(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) {
        return 0;
    }

    initialize_janet();

    int32_t capacity = *((int32_t *)Data);
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    fuzz_janet_table_weakv(capacity);
    fuzz_janet_table_weakk(capacity);
    fuzz_janet_table_weakkv(capacity);

    if (Size >= sizeof(size_t)) {
        size_t s = *((size_t *)Data);
        fuzz_janet_gcpressure(s);
    }

    janet_sweep();

    cleanup_janet();

    return 0;
}