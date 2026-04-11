#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_346(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an int32_t value
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Extract an int32_t value from the input data
    int32_t buffer_size = *(const int32_t *)data;

    // Validate the buffer_size to prevent excessive memory allocation or negative size
    if (buffer_size < 0 || buffer_size > 1024 * 1024) { // Limit buffer size to 1MB for safety
        return 0;
    }

    // Call the function-under-test
    JanetBuffer *buffer = janet_buffer(buffer_size);

    // Perform any additional operations on the buffer if needed
    // For example, you could manipulate the buffer or inspect its contents

    // Clean up if necessary
    // Note: JanetBuffer cleanup depends on how the Janet library manages memory.
    // If the library provides a specific function to free the buffer, use it here.

    return 0;
}