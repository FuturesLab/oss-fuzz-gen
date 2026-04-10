#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/hoextdown/src/buffer.h" // Correct path to the actual header file

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Ensure size is greater than 0 to have at least one byte to use
    if (size == 0) {
        return 0;
    }

    // Initialize a hoedown_buffer with the given size
    hoedown_buffer *buffer = hoedown_buffer_new(size);
    if (buffer == NULL) {
        return 0;
    }

    // Put the entire input data into the buffer
    hoedown_buffer_put(buffer, data, size);

    // Optionally, perform additional operations on the buffer if needed
    // For example, you can call other hoedown_buffer functions to test them

    // Free the buffer after use
    hoedown_buffer_free(buffer);

    return 0;
}