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
#include <stdio.h>
#include <stdlib.h>
#include "janet.h"

// Helper function to generate a random pointer
static void *random_pointer() {
    uintptr_t random_value = (uintptr_t)malloc(1); // Allocate a byte to get a valid pointer
    return (void *)random_value;
}

// Initialize Janet VM
static void initialize_janet_vm() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

int LLVMFuzzerTestOneInput_541(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) {
        return 0; // Not enough data to proceed
    }

    // Initialize Janet VM
    initialize_janet_vm();

    // Prepare inputs
    void *pointer = random_pointer();
    const void *cpointer = random_pointer();
    uint64_t tagmask = *((uint64_t *)Data);
    uint64_t bits = *((uint64_t *)Data);
    uint64_t u64_value = *((uint64_t *)Data);

    // Target API function calls
    Janet result1 = janet_nanbox_from_pointer(pointer, tagmask);
    Janet result2 = janet_nanbox_from_cpointer(cpointer, tagmask);
    Janet result3 = janet_wrap_u64(u64_value);
    Janet result4 = janet_nanbox_from_bits(bits);

    // Cleanup
    free(pointer);
    free((void *)cpointer);

    // Use the results to prevent optimization
    if (result1.u64 == 0 || result2.u64 == 0 || result3.u64 == 0 || result4.u64 == 0) {
        return 1; // Arbitrary condition to use results
    }

    return 0;
}