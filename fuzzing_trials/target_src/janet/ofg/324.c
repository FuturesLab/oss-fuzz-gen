#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this header for memcpy

// Assume janet_free is declared in an included header file or external library.
void janet_free(void *ptr);

int LLVMFuzzerTestOneInput_324(const uint8_t *data, size_t size) {
    // Allocate memory for testing janet_free
    void *test_ptr = malloc(size);
    
    // Ensure the pointer is not NULL
    if (test_ptr == NULL) {
        return 0; // Exit if memory allocation failed
    }

    // Copy data to allocated memory to simulate realistic usage
    if (size > 0) {
        memcpy(test_ptr, data, size);
    }

    // Call the function-under-test
    janet_free(test_ptr);

    return 0;
}