// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
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

static void fuzz_janet_nanbox_from_cpointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *) + sizeof(uint64_t)) return;
    const void *ptr = (const void *) *(uintptr_t *)Data;
    uint64_t tagmask = *(uint64_t *)(Data + sizeof(void *));
    Janet result = janet_nanbox_from_cpointer(ptr, tagmask);
    (void)result; // Use result to prevent unused variable warning
}

static void fuzz_janet_wrap_pointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *)) return;
    void *ptr = (void *) *(uintptr_t *)Data;
    Janet result = janet_wrap_pointer(ptr);
    (void)result; // Use result to prevent unused variable warning
}

static void fuzz_janet_unwrap_pointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet janet_value;
    janet_value.u64 = *(uint64_t *)Data;
    void *result = janet_unwrap_pointer(janet_value);
    (void)result; // Use result to prevent unused variable warning
}

static void fuzz_janet_nanbox_to_pointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet janet_value;
    janet_value.u64 = *(uint64_t *)Data;
    void *result = janet_nanbox_to_pointer(janet_value);
    (void)result; // Use result to prevent unused variable warning
}

static void fuzz_janet_nanbox_from_pointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *) + sizeof(uint64_t)) return;
    void *ptr = (void *) *(uintptr_t *)Data;
    uint64_t tagmask = *(uint64_t *)(Data + sizeof(void *));
    Janet result = janet_nanbox_from_pointer(ptr, tagmask);
    (void)result; // Use result to prevent unused variable warning
}

int LLVMFuzzerTestOneInput_589(const uint8_t *Data, size_t Size) {
    fuzz_janet_nanbox_from_cpointer(Data, Size);
    fuzz_janet_wrap_pointer(Data, Size);
    fuzz_janet_unwrap_pointer(Data, Size);
    fuzz_janet_nanbox_to_pointer(Data, Size);
    fuzz_janet_nanbox_from_pointer(Data, Size);
    return 0;
}