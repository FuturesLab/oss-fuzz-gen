#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h> // Include for debugging purposes
#include "/src/hoextdown/src/buffer.h"  // Correct path for hoedown_buffer and hoedown_buffer_cstr

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Check if data is not NULL and size is greater than zero
    if (data == NULL || size == 0) {
        return 0; // Exit if data is NULL or size is zero
    }

    // Initialize hoedown_buffer
    hoedown_buffer *buffer = hoedown_buffer_new(size);
    if (buffer == NULL) {
        return 0; // Exit if buffer creation failed
    }

    // Ensure the buffer is not empty
    hoedown_buffer_put(buffer, data, size);

    // Call the function-under-test
    const char *result = hoedown_buffer_cstr(buffer);

    // Check if result is NULL to prevent further issues
    if (result == NULL) {
        hoedown_buffer_free(buffer);
        return 0; // Exit if result is NULL
    }

    // Use the result in some way to ensure it's being processed
    // For demonstration, we'll simply check the length
    size_t result_length = strlen(result);
    printf("Result length: %zu\n", result_length); // Debugging: print result length

    // Clean up
    hoedown_buffer_free(buffer);

    return 0;
}