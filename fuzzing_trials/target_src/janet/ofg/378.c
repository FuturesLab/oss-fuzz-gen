#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test
void *janet_realloc(void *ptr, size_t size);

int LLVMFuzzerTestOneInput_378(const uint8_t *data, size_t size) {
    // Ensure there is enough data to make a meaningful call
    if (size < sizeof(size_t)) {
        return 0;
    }

    // Use the first part of the data as the size for reallocation
    size_t new_size = *((size_t *)data);

    // Allocate initial memory
    void *initial_ptr = malloc(16); // Start with a small allocation
    if (!initial_ptr) {
        return 0; // If malloc fails, return early
    }

    // Initialize the allocated memory with some data to simulate real-world usage
    memset(initial_ptr, 0xAB, 16);

    // Call the function-under-test
    void *new_ptr = janet_realloc(initial_ptr, new_size);

    // If reallocation failed, free the initial pointer
    if (!new_ptr) {
        free(initial_ptr);
    } else {
        // Free the newly allocated memory if it was successful
        free(new_ptr);
    }

    return 0;
}