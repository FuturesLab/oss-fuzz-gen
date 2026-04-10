#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Function-under-test
void * hoedown_malloc(size_t);

// Fuzzing harness
int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Ensure the size is non-zero to avoid undefined behavior in malloc
    if (size == 0) {
        return 0;
    }

    // Use the size of the input data as the size for hoedown_malloc
    void *allocated_memory = hoedown_malloc(size);

    // Free the allocated memory to prevent memory leaks
    if (allocated_memory != NULL) {
        free(allocated_memory);
    }

    return 0;
}