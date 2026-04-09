#include <stdint.h>
#include <stddef.h>
#include "janet.h" // Assuming the Janet library provides this header

// Remove 'extern "C"' as it is not needed in C code
int LLVMFuzzerTestOneInput_1416(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a uint16_t
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Initialize JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10); // Initialize with a default size

    // Extract a uint16_t value from the data
    uint16_t value = *((uint16_t *)data);

    // Call the function-under-test
    janet_buffer_push_u16(&buffer, value);

    // Clean up
    janet_buffer_deinit(&buffer);

    return 0;
}