#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_347(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t)) {
        return 0;
    }

    int32_t buffer_size = *(int32_t *)data;

    // Ensure buffer_size is positive and within a reasonable limit to prevent issues
    if (buffer_size <= 0 || buffer_size > 1024 * 1024) { // Limit buffer size to 1MB
        return 0;
    }

    // Call the function-under-test
    JanetBuffer *buffer = janet_buffer(buffer_size);

    // Use the buffer in some way to maximize fuzzing effect
    if (buffer != NULL) {
        // Example usage of the buffer
        janet_buffer_push_u8(buffer, 0x55); // Push a sample byte into the buffer

        // Clean up
        janet_buffer_deinit(buffer);
    }

    return 0;
}