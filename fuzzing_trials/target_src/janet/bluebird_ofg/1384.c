#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1384(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Initialize JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10);  // Initialize with a small size

    // Extract an int32_t from the input data
    int32_t count = *(const int32_t *)data;

    // Ensure count is within a reasonable range
    if (count < 0) {
        count = 0;
    } else if ((size_t)count > buffer.capacity) {
        count = buffer.capacity;
    }

    // Call the function-under-test
    janet_buffer_setcount(&buffer, count);

    // Use the buffer in some way to ensure code coverage
    if (buffer.count > 0) {
        // Perform some operation that utilizes the buffer
        // For example, accessing the buffer data
        uint8_t first_byte = buffer.data[0];
        (void)first_byte; // Use the variable to avoid compiler warnings
    }

    // Clean up
    janet_buffer_deinit(&buffer);

    return 0;
}