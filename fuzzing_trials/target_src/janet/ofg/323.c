#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy

// Function-under-test
void janet_free(void *ptr);

int LLVMFuzzerTestOneInput_323(const uint8_t *data, size_t size) {
    // Allocate memory to be freed
    void *ptr = malloc(size ? size : 1); // Ensure size is not zero for malloc

    // Ensure ptr is not NULL
    if (ptr == NULL) {
        return 0;
    }

    // Copy the fuzz data into the allocated memory
    if (size > 0) {
        memcpy(ptr, data, size);
    }

    // Call the function-under-test with the allocated memory
    janet_free(ptr);

    // Ensure the function is tested with a non-null input
    // Allocate another block of memory and free it
    void *additional_ptr = malloc(1); // Allocate a small block of memory
    if (additional_ptr != NULL) {
        // Fill the additional memory with some data
        memset(additional_ptr, 0xAB, 1); // Fill with a pattern

        // Call the function-under-test again
        janet_free(additional_ptr);
    }

    return 0;
}