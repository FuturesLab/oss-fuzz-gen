// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_nanbox_from_cpointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *) + sizeof(uint64_t)) return;
    const void *p = (const void *)*(uintptr_t *)Data;
    uint64_t tagmask = *(uint64_t *)(Data + sizeof(void *));
    Janet result = janet_nanbox_from_cpointer(p, tagmask);
}

static void fuzz_unwrap_pointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x = *(Janet *)Data;
    void *result = janet_unwrap_pointer(x);
}

static void fuzz_nanbox_from_bits(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return;
    uint64_t bits = *(uint64_t *)Data;
    Janet result = janet_nanbox_from_bits(bits);
}

static void fuzz_nanbox_to_pointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x = *(Janet *)Data;
    void *result = janet_nanbox_to_pointer(x);
}

static void fuzz_nanbox_from_pointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *) + sizeof(uint64_t)) return;
    void *p = (void *)*(uintptr_t *)Data;
    uint64_t tagmask = *(uint64_t *)(Data + sizeof(void *));
    Janet result = janet_nanbox_from_pointer(p, tagmask);
}

int LLVMFuzzerTestOneInput_692(const uint8_t *Data, size_t Size) {
    fuzz_nanbox_from_cpointer(Data, Size);
    fuzz_unwrap_pointer(Data, Size);
    fuzz_nanbox_from_bits(Data, Size);
    fuzz_nanbox_to_pointer(Data, Size);
    fuzz_nanbox_from_pointer(Data, Size);
    return 0;
}