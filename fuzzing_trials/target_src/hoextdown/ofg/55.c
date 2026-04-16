#include <stdint.h>
#include <stddef.h>
#include "/src/hoextdown/src/buffer.h"  // Correct path for hoedown_buffer

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Initialize a hoedown_buffer
    hoedown_buffer *buffer = hoedown_buffer_new(64);  // Allocate a buffer with an initial size of 64 bytes

    // Ensure the data size is at least 4 bytes to form a valid unsigned int
    if (size < sizeof(unsigned int)) {
        hoedown_buffer_free(buffer);
        return 0;
    }

    // Extract an unsigned int from the data
    unsigned int utf8_char = *((unsigned int *)data);

    // Call the function-under-test
    hoedown_buffer_put_utf8(buffer, utf8_char);

    // Clean up
    hoedown_buffer_free(buffer);

    return 0;
}