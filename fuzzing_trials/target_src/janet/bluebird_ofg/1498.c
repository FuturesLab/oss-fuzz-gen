#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1498(const uint8_t *data, size_t size) {
    // Ensure that size is within the range of int32_t
    if (size > INT32_MAX) {
        return 0;
    }

    // Ensure that data is not null and size is greater than zero
    if (data == NULL || size == 0) {
        return 0;
    }

    // Cast size to int32_t
    int32_t length = (int32_t)size;

    // Initialize the Janet environment
    janet_init();

    // Call the function-under-test
    JanetString result = janet_string(data, length);

    // Use the result to avoid any compiler optimizations that might skip the call
    // For example, you might want to check the length of the result
    if (janet_string_length(result) != length) {
        // Handle unexpected result length
    }

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}