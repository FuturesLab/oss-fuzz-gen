#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"  // Include the Janet library header for JanetBuffer

int LLVMFuzzerTestOneInput_286(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract an int32_t
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Initialize a JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10); // Initialize with a small size

    // Extract an int32_t value from the input data
    int32_t extra_space = *((int32_t *)data);

    // Call the function-under-test
    janet_buffer_extra(&buffer, extra_space);

    // Clean up
    janet_buffer_deinit(&buffer);

    return 0;
}