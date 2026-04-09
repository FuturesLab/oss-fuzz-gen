#include <stdint.h>
#include <stdlib.h>
#include "janet.h" // Assuming this is the header file where JanetBuffer is defined

int LLVMFuzzerTestOneInput_1385(const uint8_t *data, size_t size) {
    // Initialize a JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10); // Initializing with a size of 10

    // Ensure there is enough data to read a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Read a uint32_t from the input data
    uint32_t value;
    value = *((uint32_t *)data);

    // Call the function-under-test
    janet_buffer_push_u32(&buffer, value);

    // Clean up
    janet_buffer_deinit(&buffer);

    return 0;
}