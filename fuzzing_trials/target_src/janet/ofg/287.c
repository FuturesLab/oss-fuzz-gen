#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h" // Assuming the Janet library provides this header

int LLVMFuzzerTestOneInput_287(const uint8_t *data, size_t size) {
    // Initialize JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10); // Initialize with a default size of 10

    // Ensure size is not zero to avoid undefined behavior
    if (size == 0) {
        return 0;
    }

    // Use the first 4 bytes of data as an int32_t for the second parameter
    int32_t extra = 0;
    if (size >= sizeof(int32_t)) {
        extra = *(int32_t *)data;
    }

    // Call the function under test
    janet_buffer_extra(&buffer, extra);

    // Clean up
    janet_buffer_deinit(&buffer);

    return 0;
}