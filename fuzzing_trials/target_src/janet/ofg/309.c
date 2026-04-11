#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h" // Assuming this is the header where JanetBuffer is defined

void janet_buffer_ensure(JanetBuffer *buffer, int32_t capacity, int32_t growth);

int LLVMFuzzerTestOneInput_309(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // No data to process
    }

    // Initialize a JanetBuffer with random data
    JanetBuffer buffer;
    buffer.data = (uint8_t *)malloc(size);
    if (buffer.data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(buffer.data, data, size);
    buffer.capacity = (int32_t)size;
    buffer.count = (int32_t)size / 2; // Arbitrary count less than or equal to size

    // Define some test values for capacity and growth, including randomization
    int32_t test_capacity[] = {0, 10, 20, 30, 40, 50, (int32_t)size * 2, (int32_t)rand() % (size * 3)};
    int32_t test_growth[] = {0, 1, 2, 3, 4, 5, (int32_t)size / 2, (int32_t)rand() % (size / 2 + 1)};

    // Fuzz janet_buffer_ensure with different capacity and growth values
    for (size_t i = 0; i < sizeof(test_capacity) / sizeof(test_capacity[0]); i++) {
        for (size_t j = 0; j < sizeof(test_growth) / sizeof(test_growth[0]); j++) {
            janet_buffer_ensure(&buffer, test_capacity[i], test_growth[j]);

            // Add additional checks and manipulations to ensure more comprehensive fuzzing
            if (buffer.capacity > 0 && buffer.data != NULL) {
                // Access and manipulate memory within the buffer's capacity
                for (size_t k = 0; k < buffer.capacity; k++) {
                    buffer.data[k] = (uint8_t)(buffer.data[k] ^ 0xFF); // Simple transformation
                }
            }

            // Check for potential memory corruption by accessing beyond the current count
            if (buffer.count < buffer.capacity) {
                for (size_t k = buffer.count; k < buffer.capacity; k++) {
                    // Attempt to read and write beyond the current count to test buffer handling
                    buffer.data[k] = (uint8_t)(buffer.data[k] ^ 0xAA); // Another transformation
                }
            }

            // Verify buffer's integrity after operations
            if (buffer.data != NULL) {
                for (size_t k = 0; k < buffer.count; k++) {
                    if (buffer.data[k] == 0) {
                        // Log or handle unexpected zero values
                    }
                }
            }
        }
    }

    // Free allocated memory
    free(buffer.data);

    return 0;
}