#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_209(const uint8_t *data, size_t size) {
    // Initialize Janet environment
    janet_init();

    // Create a JanetBuffer
    JanetBuffer *buffer = janet_buffer(0);

    // Ensure that the size is within the range of int32_t
    int32_t dataSize = (size > INT32_MAX) ? INT32_MAX : (int32_t)size;

    // Call the function-under-test
    janet_buffer_push_bytes(buffer, data, dataSize);

    // Clean up
    janet_deinit();

    return 0;
}