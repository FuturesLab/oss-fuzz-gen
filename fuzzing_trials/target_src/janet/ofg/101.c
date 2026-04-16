#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Function-under-test
void *janet_malloc(size_t size);

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Ensure size is not zero to avoid undefined behavior in malloc
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test with the provided size
    void *allocated_memory = janet_malloc(size);

    // Check if memory was successfully allocated
    if (allocated_memory != NULL) {
        // Simulate some usage of the allocated memory
        // For example, write the input data to the allocated memory
        size_t copy_size = size < 1024 ? size : 1024; // Limit to 1024 bytes
        for (size_t i = 0; i < copy_size; i++) {
            ((uint8_t *)allocated_memory)[i] = data[i];
        }

        // Free the allocated memory
        free(allocated_memory);
    }

    return 0;
}