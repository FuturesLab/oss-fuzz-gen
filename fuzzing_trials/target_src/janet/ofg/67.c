#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <janet.h>

extern JanetFiber *janet_getfiber(const Janet *, int32_t);

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Create a Janet value from the input data
    Janet janet_value = janet_wrap_number(*(const double *)data);

    // Ensure the index is within a reasonable range
    int32_t index = size % 100; // Arbitrary limit for index

    // Call the function-under-test
    JanetFiber *fiber = janet_getfiber(&janet_value, index);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}