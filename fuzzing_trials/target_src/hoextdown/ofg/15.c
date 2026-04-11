#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/hoextdown/src/buffer.h" // Corrected path for hoedown_buffer

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Ensure there is at least some data to work with
    if (size < 1) {
        return 0;
    }

    // Initialize hoedown_buffer
    hoedown_buffer *buffer = hoedown_buffer_new(64); // Initial size, arbitrary non-zero value

    // Use the first byte of the input data to determine the size for hoedown_buffer_grow
    size_t grow_size = (size_t)data[0];

    // Call the function under test
    hoedown_buffer_grow(buffer, grow_size);

    // Clean up
    hoedown_buffer_free(buffer);

    return 0;
}