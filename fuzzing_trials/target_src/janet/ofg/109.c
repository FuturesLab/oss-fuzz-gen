#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy
#include "janet.h" // Assuming janet.h is the header file where JanetBuffer is defined

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Initialize a JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10); // Initializing with a small size for testing

    // Extract a uint64_t value from the input data
    uint64_t value;
    memcpy(&value, data, sizeof(uint64_t));

    // Call the function-under-test
    janet_buffer_push_u64(&buffer, value);

    // Clean up
    janet_buffer_deinit(&buffer);

    return 0;
}