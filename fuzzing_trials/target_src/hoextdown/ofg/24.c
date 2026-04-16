#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/hoextdown/src/buffer.h"  // Correct path for hoedown_buffer

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Initialize a hoedown_buffer
    hoedown_buffer *buffer = hoedown_buffer_new(64);  // Initializing with a size of 64

    // Ensure the buffer is not NULL
    if (buffer == NULL) {
        return 0;
    }

    // Call the function-under-test
    hoedown_buffer_put(buffer, data, size);

    // Clean up
    hoedown_buffer_free(buffer);

    return 0;
}