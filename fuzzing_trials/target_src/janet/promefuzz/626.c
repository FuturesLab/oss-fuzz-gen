// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_wrap_s64 at inttypes.c:180:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void initialize_janet() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

static void fuzz_janet_wrap_s64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int64_t)) return;
    int64_t value = *(int64_t *)Data;
    Janet result = janet_wrap_s64(value);
    // Optionally perform operations on result
    (void)result; // Suppress unused variable warning
}

static void fuzz_janet_wrap_pointer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *)) return;
    void *ptr = (void *)Data;
    Janet result = janet_wrap_pointer(ptr);
    // Optionally perform operations on result
    (void)result; // Suppress unused variable warning
}

static void fuzz_janet_wrap_nil() {
    Janet result = janet_wrap_nil();
    // Optionally perform operations on result
    (void)result; // Suppress unused variable warning
}

int LLVMFuzzerTestOneInput_626(const uint8_t *Data, size_t Size) {
    initialize_janet();
    fuzz_janet_wrap_s64(Data, Size);
    fuzz_janet_wrap_pointer(Data, Size);
    fuzz_janet_wrap_nil();
    return 0;
}