#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    if (size < 2) { // Ensure there is enough data for operations
        return 0;
    }

    // Initialize Janet
    janet_init();

    // Create a Janet object from the input data
    Janet janet_data = janet_wrap_number((double)data[0]);

    // Ensure the index is within a reasonable range
    int32_t index = (int32_t)(data[1] % 10); // Limiting index to 0-9

    // Create a buffer to work with
    JanetBuffer *buffer = janet_buffer(10);

    // Use the buffer with some operation
    janet_buffer_push_u8(buffer, data[0]);

    // Clean up Janet
    janet_deinit();

    return 0;
}