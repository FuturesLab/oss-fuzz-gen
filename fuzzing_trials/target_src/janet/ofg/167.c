#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

// Function-under-test declaration
int janet_cryptorand(uint8_t *buffer, size_t size);

int LLVMFuzzerTestOneInput_167(const uint8_t *data, size_t size) {
    // Allocate a buffer for the random data
    uint8_t buffer[256]; // Example buffer size, adjust if necessary

    // Ensure the size does not exceed the buffer
    if (size > sizeof(buffer)) {
        size = sizeof(buffer);
    }

    // Copy the input data to the buffer to ensure it's not null
    memcpy(buffer, data, size);

    // Call the function-under-test
    janet_cryptorand(buffer, size);

    return 0;
}