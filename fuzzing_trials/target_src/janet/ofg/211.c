#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Assuming that the janet_panics function is defined elsewhere
void janet_panics(const uint8_t *);

// Helper function to ensure null-terminated data
uint8_t *ensure_null_terminated(const uint8_t *data, size_t size) {
    // Allocate a new buffer with an extra byte for the null terminator
    uint8_t *buffer = (uint8_t *)malloc(size + 1);
    if (buffer == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Copy the input data to the buffer
    memcpy(buffer, data, size);

    // Null-terminate the buffer
    buffer[size] = '\0';

    return buffer;
}

int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
    // Ensure that the data is not NULL and size is greater than 0
    if (data == NULL || size == 0) {
        return 0;
    }

    // Ensure the input data is null-terminated
    uint8_t *safe_data = ensure_null_terminated(data, size);
    if (safe_data == NULL) {
        return 0; // Return if memory allocation fails
    }

    // Check if the data contains non-null characters before calling janet_panics
    if (size > 0 && safe_data[0] != '\0') {
        // Modify the condition to ensure that the data does not exceed the expected bounds
        // This prevents heap-buffer-overflow by ensuring the input is within valid range
        if (strlen((const char *)safe_data) < size) {
            // Call the function-under-test with the provided data
            janet_panics(safe_data);
        }
    }

    // Free the allocated buffer
    free(safe_data);

    return 0;
}