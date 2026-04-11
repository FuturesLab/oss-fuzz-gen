#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free
#include "/src/hoextdown/src/buffer.h"  // Correct path for hoedown_buffer

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to split into two parts
    if (size < 2) {
        return 0;
    }

    // Allocate and initialize a hoedown_buffer
    hoedown_buffer buffer;
    buffer.data = (uint8_t *)data;  // Point to the fuzz data
    buffer.size = size / 2;         // Use half of the data for the buffer
    buffer.asize = buffer.size;
    buffer.unit = 1;

    // Use the second half of the data as a string
    const char *prefix = (const char *)(data + buffer.size);
    size_t prefix_length = size - buffer.size;

    // Ensure the prefix is null-terminated
    char *null_terminated_prefix = (char *)malloc(prefix_length + 1);
    if (null_terminated_prefix == NULL) {
        return 0;
    }
    memcpy(null_terminated_prefix, prefix, prefix_length);
    null_terminated_prefix[prefix_length] = '\0';

    // Call the function-under-test
    int result = hoedown_buffer_prefix(&buffer, null_terminated_prefix);

    // Clean up
    free(null_terminated_prefix);

    return 0;
}