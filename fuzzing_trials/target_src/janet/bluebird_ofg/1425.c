#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1425(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure the data size is not zero to create a valid symbol
    if (size == 0) {
        janet_deinit();
        return 0;
    }

    // Ensure the data is null-terminated by copying it to a new buffer
    char *buffer = (char *)malloc(size + 1);
    if (!buffer) {
        janet_deinit();
        return 0; // Handle allocation failure
    }
    memcpy(buffer, data, size);
    buffer[size] = '\0'; // Null-terminate the buffer

    // Create a JanetSymbol from the input data
    JanetSymbol symbol = janet_symbol(buffer, (int32_t)size);

    // Free the buffer after use
    free(buffer);

    // Call the function-under-test
    Janet result = janet_wrap_symbol(symbol);

    // Use the result in some way to prevent compiler optimizations from removing the call
    // This can be a simple operation like checking if the result is not null
    if (!janet_checktype(result, JANET_NIL)) {
        // Do nothing, just a placeholder to use the result
    }

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}