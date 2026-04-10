#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

// Function-under-test declaration
int janet_cryptorand(uint8_t *buffer, size_t size);

int LLVMFuzzerTestOneInput_1280(const uint8_t *data, size_t size) {
    // Allocate a buffer for the random data
    uint8_t buffer[256]; // Example buffer size, adjust if necessary

    // Ensure the size does not exceed the buffer
    if (size > sizeof(buffer)) {
        size = sizeof(buffer);
    }

    // Copy the input data to the buffer to ensure it's not null
    memcpy(buffer, data, size);

    // Call the function-under-test
    int result = janet_cryptorand(buffer, size);

    // Check the result or buffer content if applicable
    // This is a placeholder for any validation logic needed
    if (result != 0) {
        // Handle error if needed
    }

    // Optionally, add more checks on the buffer to ensure it is modified as expected
    // Example: Check if the buffer is filled with random data
    for (size_t i = 0; i < size; i++) {
        if (buffer[i] == 0) {
            // Handle unexpected zero value if the function should not produce zeros
        }
    }

    return 0;
}