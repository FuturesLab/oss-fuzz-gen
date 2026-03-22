#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
    void * tj3Alloc(size_t);
}

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Ensure the size is non-zero to allocate memory
    if (size == 0) {
        return 0;
    }

    // Use the size of the input data as the size parameter for tj3Alloc
    size_t alloc_size = size;

    // Call the function-under-test
    void *allocated_memory = tj3Alloc(alloc_size);

    // If allocation was successful, free the allocated memory
    if (allocated_memory != NULL) {
        free(allocated_memory);
    }

    return 0;
}