#include <stdint.h>
#include <stddef.h>
#include "janet.h"

// Fuzzing harness for janet_to_string_b
int LLVMFuzzerTestOneInput_1464(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Create a JanetBuffer
    JanetBuffer *buffer = janet_buffer(size);

    // Create a Janet object from the input data
    Janet janet_data;
    if (size >= sizeof(Janet)) {
        // Assuming the data is large enough to hold a Janet type
        janet_data = *(Janet *)data;
    } else {
        // If not enough data, use a default Janet value
        janet_data = janet_wrap_nil();
    }

    // Call the function-under-test
    janet_to_string_b(buffer, janet_data);

    // Clean up
    janet_deinit();

    return 0;
}