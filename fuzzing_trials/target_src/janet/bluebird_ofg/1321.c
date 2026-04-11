#include <stdint.h>
#include <stddef.h>
#include "janet.h" // Assuming the Janet library provides this header

// Function-under-test
void janet_buffer_push_u64(JanetBuffer *buffer, uint64_t value);

int LLVMFuzzerTestOneInput_1321(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Initialize a JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10); // Initializing with a capacity of 10

    // Extract a uint64_t value from the input data
    uint64_t value = *(const uint64_t *)data;

    // Call the function-under-test
    janet_buffer_push_u64(&buffer, value);

    // Clean up
    janet_buffer_deinit(&buffer);

    return 0;
}