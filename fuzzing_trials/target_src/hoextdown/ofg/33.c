#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy
#include "/src/hoextdown/src/buffer.h" // Correct path for hoedown_buffer and hoedown_buffer_slurp

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Return early if size is zero, as there's nothing to process
    if (size == 0) {
        return 0;
    }

    // Initialize a hoedown_buffer
    hoedown_buffer buffer;
    buffer.data = (uint8_t *)malloc(size);
    if (buffer.data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    buffer.size = size;
    buffer.asize = size;
    buffer.unit = 1;

    // Copy the input data to the buffer
    memcpy(buffer.data, data, size);

    // Call the function-under-test with a valid slurp size
    // Use a slurp size that ensures the function processes the data
    size_t slurp_size = size > 1 ? size - 1 : 1; // Ensure slurp_size is non-zero and meaningful
    hoedown_buffer_slurp(&buffer, slurp_size);

    // Clean up
    free(buffer.data);

    return 0;
}