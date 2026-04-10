#include <stdint.h>
#include <stddef.h>
#include "janet.h"
#include <string.h>
#include <stdlib.h>

// Initialize the Janet environment
static void initialize_janet_1320() {
    janet_init();
}

int LLVMFuzzerTestOneInput_1320(const uint8_t *data, size_t size) {
    // Ensure that the data size is large enough to extract necessary parameters
    if (size < sizeof(int32_t) * 2 + 1) {
        return 0;
    }

    // Initialize Janet if not already initialized
    static int janet_initialized = 0;
    if (!janet_initialized) {
        initialize_janet_1320();
        janet_initialized = 1;
    }

    // Extract int32_t parameters from data
    int32_t arg1 = *((int32_t *)(data + 1));
    int32_t arg2 = *((int32_t *)(data + 1 + sizeof(int32_t)));

    // Ensure the string is null-terminated
    size_t string_length = size - (1 + 2 * sizeof(int32_t));
    char *arg3 = (char *)(data + 1 + 2 * sizeof(int32_t));
    char *null_terminated_arg3 = (char *)malloc(string_length + 1);
    if (!null_terminated_arg3) {
        return 0; // Handle malloc failure
    }
    memcpy(null_terminated_arg3, arg3, string_length);
    null_terminated_arg3[string_length] = '\0';

    // Initialize Janet array
    Janet janetArray[1];
    janetArray[0] = janet_wrap_integer((int32_t)data[0]);

    // Check if the extracted string is valid for the function-under-test
    if (string_length > 0 && null_terminated_arg3[0] != '\0') {
        // Ensure arg1 and arg2 are within valid range for the function-under-test
        if (arg1 >= 0 && arg2 >= 0 && arg1 <= arg2 && arg2 < (int32_t)string_length) {
            // Call the function-under-test
            int32_t raw_result = janet_gethalfrange(janetArray, arg1, arg2, null_terminated_arg3);
            Janet result = janet_wrap_integer(raw_result);

            // Use result in a way that prevents compiler optimizations from removing the call
            (void)result;
        }
    }

    // Free allocated memory
    free(null_terminated_arg3);

    return 0;
}