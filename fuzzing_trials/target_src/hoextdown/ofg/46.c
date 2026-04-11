#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Function-under-test
void * hoedown_malloc(size_t size);

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Ensure the size is non-zero to avoid undefined behavior
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test with the size derived from the input data
    void *result = hoedown_malloc(size);

    // If the allocation was successful, free the allocated memory
    if (result != NULL) {
        free(result);
    }

    return 0;
}