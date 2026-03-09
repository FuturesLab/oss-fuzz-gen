#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"
#include "magic.h"

extern "C" {
    // Function signature from the project-under-test
    int magic_load_buffers(struct magic_set *, void **, size_t *, size_t);
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Declare and initialize necessary variables
    struct magic_set *magic = magic_open(MAGIC_NONE);
    void *buffers[1];
    size_t sizes[1];

    // Ensure magic is not NULL
    if (magic == NULL) {
        return 0;
    }

    // Initialize buffers and sizes with the input data
    buffers[0] = (void *)data;
    sizes[0] = size;

    // Call the function-under-test
    magic_load_buffers(magic, buffers, sizes, 1);

    // Clean up
    magic_close(magic);

    return 0;
}