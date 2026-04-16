#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function signature for the function-under-test
void *hoedown_realloc(void *ptr, size_t size);

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Initialize a non-NULL pointer with some allocated memory
    void *ptr = malloc(1); // Initially allocate 1 byte

    // Ensure that size is non-zero for meaningful reallocation
    if (size == 0) {
        size = 1; // Set size to a non-zero value
    }

    // Use the input data to influence the behavior of hoedown_realloc
    size_t new_size = size % 1024; // Limit the size to a reasonable value

    // Call the function-under-test with the pointer and new size
    void *new_ptr = hoedown_realloc(ptr, new_size);

    // Check if realloc was successful
    if (new_ptr != NULL) {
        // Optionally use the new_ptr to do something meaningful
        memset(new_ptr, 0, new_size); // Initialize the memory to zero
    }

    // Free the newly allocated memory to prevent memory leaks
    free(new_ptr);

    return 0;
}