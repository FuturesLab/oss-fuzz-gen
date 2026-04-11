#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/hoextdown/src/buffer.h"  // Correct path for hoedown_buffer

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Initialize a hoedown_buffer
    hoedown_buffer *buffer = hoedown_buffer_new(size > 0 ? size : 1);  // Ensure buffer size is at least 1

    // Iterate over the input data and call hoedown_buffer_putc for each byte
    for (size_t i = 0; i < size; ++i) {
        hoedown_buffer_putc(buffer, data[i]);
    }

    // Clean up the buffer
    hoedown_buffer_free(buffer);

    return 0;
}