// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_wrap_u64 at inttypes.c:186:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
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

static int janet_initialized = 0;

static void initialize_janet() {
    if (!janet_initialized) {
        janet_init();
        janet_initialized = 1;
    }
}

static void fuzz_janet_nanbox_from_pointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *) + sizeof(uint64_t)) return;
    void *p = *(void **)Data;
    uint64_t tagmask = *(uint64_t *)(Data + sizeof(void *));
    Janet result = janet_nanbox_from_pointer(p, tagmask);
    (void)result; // Prevent unused variable warning
}

static void fuzz_janet_nanbox_from_cpointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *) + sizeof(uint64_t)) return;
    const void *p = *(const void **)Data;
    uint64_t tagmask = *(uint64_t *)(Data + sizeof(void *));
    Janet result = janet_nanbox_from_cpointer(p, tagmask);
    (void)result; // Prevent unused variable warning
}

static void fuzz_janet_wrap_u64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return;
    uint64_t x = *(uint64_t *)Data;
    Janet result = janet_wrap_u64(x);
    (void)result; // Prevent unused variable warning
}

static void fuzz_janet_nanbox_from_bits(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return;
    uint64_t bits = *(uint64_t *)Data;
    Janet result = janet_nanbox_from_bits(bits);
    (void)result; // Prevent unused variable warning
}

int LLVMFuzzerTestOneInput_327(const uint8_t *Data, size_t Size) {
    initialize_janet();
    fuzz_janet_nanbox_from_pointer(Data, Size);
    fuzz_janet_nanbox_from_cpointer(Data, Size);
    fuzz_janet_wrap_u64(Data, Size);
    fuzz_janet_nanbox_from_bits(Data, Size);
    return 0;
}