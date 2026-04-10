#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include "/src/hoextdown/src/buffer.h" // Correct path for hoedown_buffer and its functions

int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    if (size == 0) return 0; // Early exit if size is zero

    // Allocate memory for hoedown_buffer
    hoedown_buffer *buffer = hoedown_buffer_new(size);
    if (buffer == NULL) return 0;

    // Copy the input data into the buffer's data
    hoedown_buffer_put(buffer, data, size);

    // Call the function under test with a meaningful size
    hoedown_buffer_slurp(buffer, size / 2); // Use half of the size for slurping

    // Clean up
    hoedown_buffer_free(buffer);

    return 0;
}