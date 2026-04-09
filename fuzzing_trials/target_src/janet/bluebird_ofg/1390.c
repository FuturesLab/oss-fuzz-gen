#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include "janet.h"
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_1390(const uint8_t *data, size_t size) {
    // Ensure the size is within a valid range for int32_t
    if (size == 0 || size > INT32_MAX) {
        return 0;
    }

    // Initialize the Janet environment
    janet_init();

    // Allocate memory for a null-terminated string
    uint8_t *null_terminated_data = (uint8_t *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        janet_deinit();
        return 0;
    }

    // Copy the input data and null-terminate it
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    const uint8_t *symbol = janet_symbol(null_terminated_data, (int32_t)size);

    // Use the symbol in some way to prevent compiler optimizations from removing the call
    // Here we just check if the symbol is NULL
    if (symbol == NULL) {
        free(null_terminated_data);
        janet_deinit();
        return 0;
    }

    // Additional logic could be added here to further utilize `symbol`

    // Free the allocated memory
    free(null_terminated_data);

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}