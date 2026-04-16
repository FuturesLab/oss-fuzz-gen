#include <stdint.h>
#include <stddef.h>
#include "janet.h"
#include <string.h>
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_1391(const uint8_t *data, size_t size) {
    // Ensure that size is not zero and does not exceed the maximum value for int32_t
    if (size == 0 || size > INT32_MAX) {
        return 0;
    }

    // Cast size to int32_t as required by the function signature
    int32_t len = (int32_t)size;

    // Ensure the data is null-terminated for safety, allocate a new buffer
    uint8_t *safe_data = (uint8_t *)malloc(len + 1);
    if (safe_data == NULL) {
        return 0; // Memory allocation failed
    }
    memcpy(safe_data, data, len);
    safe_data[len] = '\0'; // Null-terminate the data

    // Validate that the data is not empty after null-termination
    if (safe_data[0] == '\0') {
        free(safe_data);
        return 0;
    }

    // Initialize Janet runtime
    janet_init();

    // Call the function-under-test
    JanetSymbol symbol = janet_symbol(safe_data, len);

    // Use the symbol in some way to ensure it's not optimized out
    JanetArray *array = janet_array(1);
    janet_array_push(array, janet_wrap_symbol(symbol));

    // Clean up Janet runtime
    janet_deinit();

    // Free the allocated memory
    free(safe_data);

    return 0;
}