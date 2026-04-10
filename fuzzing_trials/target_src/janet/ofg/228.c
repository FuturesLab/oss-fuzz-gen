#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Assuming JanetString is a type defined elsewhere in the codebase
typedef struct {
    const uint8_t *data;
    size_t length;
} JanetString;

// Mock implementation of janet_string_end for demonstration purposes
JanetString janet_string_end_228(uint8_t *str) {
    JanetString result;
    result.data = str;
    result.length = strlen((const char *)str);
    return result;
}

int LLVMFuzzerTestOneInput_228(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for string operations
    if (size == 0) {
        return 0; // No input data to process
    }

    uint8_t *null_terminated_data = (uint8_t *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Memory allocation failed
    }

    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    JanetString result = janet_string_end_228(null_terminated_data);

    // Use the result in some way to prevent compiler optimizations from removing the call
    // Additionally, perform some operations to ensure the function is effectively tested
    if (result.length > 0) {
        // Access the data to ensure it's being used
        volatile uint8_t first_char = result.data[0];
        (void)first_char; // Use the first_char to ensure it's not optimized away
    }

    // Clean up allocated memory
    free(null_terminated_data);

    return 0;
}