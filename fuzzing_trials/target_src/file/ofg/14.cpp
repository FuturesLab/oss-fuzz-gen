#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <magic.h>

extern "C" {
    // Include necessary C headers and ensure the function-under-test is declared
    #include <magic.h>
}

// Define the fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for the function-under-test
    struct magic_set *ms;
    void *buffers[1];
    size_t sizes[1];
    size_t count = 1;

    // Initialize the magic_set structure
    ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0;
    }

    // Allocate memory for the buffer and copy the input data into it
    buffers[0] = malloc(size);
    if (buffers[0] == NULL) {
        magic_close(ms);
        return 0;
    }
    memcpy(buffers[0], data, size);
    sizes[0] = size;

    // Call the function-under-test
    int result = magic_load_buffers(ms, buffers, sizes, count);

    // Clean up allocated resources
    free(buffers[0]);
    magic_close(ms);

    return 0;
}