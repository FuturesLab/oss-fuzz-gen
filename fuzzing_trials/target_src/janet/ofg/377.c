#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test
void *janet_realloc(void *ptr, size_t size);

int LLVMFuzzerTestOneInput_377(const uint8_t *data, size_t size) {
    // Allocate an initial buffer with some data
    size_t initial_size = size > 0 ? size : 1; // Ensure initial size is non-zero
    void *initial_buffer = malloc(initial_size);
    
    if (initial_buffer == NULL) {
        return 0; // If allocation fails, exit early
    }

    // Copy data into the initial buffer
    memcpy(initial_buffer, data, initial_size);

    // Try reallocating with different sizes
    size_t new_size1 = initial_size * 2;
    void *new_buffer1 = janet_realloc(initial_buffer, new_size1);

    if (new_buffer1 != NULL) {
        // Further reallocate with another size
        size_t new_size2 = new_size1 / 2;
        void *new_buffer2 = janet_realloc(new_buffer1, new_size2);

        // Free the final buffer if not NULL
        if (new_buffer2 != NULL) {
            free(new_buffer2);
        }
    }

    return 0;
}