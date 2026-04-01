#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <magic.h>

extern "C" {
    // Include necessary C headers and function declarations
    #include <magic.h>
}

// Fuzzing harness for the function `magic_load_buffers`
extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Initialize the magic_set structure
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0; // Return if magic_open fails
    }

    // Allocate memory for buffers
    void *buffers[1];
    size_t buffer_sizes[1];

    // Ensure the data is not NULL and size is valid
    if (size > 0) {
        buffers[0] = malloc(size);
        if (buffers[0] == NULL) {
            magic_close(magic);
            return 0; // Return if malloc fails
        }
        memcpy(buffers[0], data, size);
        buffer_sizes[0] = size;
    } else {
        buffers[0] = malloc(1); // Allocate at least 1 byte
        if (buffers[0] == NULL) {
            magic_close(magic);
            return 0; // Return if malloc fails
        }
        buffer_sizes[0] = 1;
    }

    // Call the function-under-test
    magic_load_buffers(magic, buffers, buffer_sizes, 1);

    // Clean up
    free(buffers[0]);
    magic_close(magic);

    return 0;
}