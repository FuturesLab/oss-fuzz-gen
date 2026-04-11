#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test
void *hoedown_realloc(void *ptr, size_t size);

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Ensure size is not zero to avoid undefined behavior with realloc
    if (size == 0) {
        return 0;
    }

    // Allocate initial memory block
    size_t initial_size = size / 2 + 1; // Ensure non-zero initial size
    void *initial_ptr = malloc(initial_size);
    if (initial_ptr == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy some data to the initial memory block to make the test more meaningful
    memcpy(initial_ptr, data, initial_size < size ? initial_size : size);

    // Call the function-under-test
    void *new_ptr = hoedown_realloc(initial_ptr, size);

    // Check if realloc was successful
    if (new_ptr == NULL) {
        free(initial_ptr);
        return 0;
    }

    // Optionally, perform additional operations on new_ptr to further test its validity

    // Free the allocated memory
    free(new_ptr);

    return 0;
}