#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_275(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Ensure the size is sufficient to extract an int32_t value
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Extract an int32_t value from the data
    int32_t initial_capacity = *((int32_t *)data);

    // Initialize a JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, initial_capacity);

    // Clean up Janet
    janet_deinit();

    return 0;
}