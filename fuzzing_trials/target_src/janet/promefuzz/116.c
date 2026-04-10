// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_register at janet.c:34286:6 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_getcfunction at janet.c:4522:1 in janet.h
// janet_optcfunction at janet.c:4534:1 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static Janet cfunction_sample(int32_t argc, Janet *argv) {
    (void)argc;
    (void)argv;
    return janet_wrap_nil();
}

int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet environment
    janet_init();

    // Prepare dummy file if needed
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Register a sample C function
    janet_register("dummy", cfunction_sample);

    // Test janet_wrap_cfunction
    Janet wrapped = janet_wrap_cfunction(cfunction_sample);

    // Test janet_unwrap_cfunction
    JanetCFunction unwrapped = janet_unwrap_cfunction(wrapped);

    // Prepare Janet array for testing
    Janet array[2];
    array[0] = wrapped;
    array[1].u64 = 0;

    // Test janet_getcfunction
    if (Size > 1) {
        int32_t index = Data[0] % 2; // Ensure index is within bounds
        JanetCFunction cfun = janet_getcfunction(array, index);
        (void)cfun;
    }

    // Test janet_optcfunction
    if (Size > 2) {
        int32_t index = Data[1] % 3; // Ensure index is within bounds
        JanetCFunction optcfun = janet_optcfunction(array, 2, index, cfunction_sample);
        (void)optcfun;
    }

    // Cleanup Janet environment
    janet_deinit();

    return 0;
}