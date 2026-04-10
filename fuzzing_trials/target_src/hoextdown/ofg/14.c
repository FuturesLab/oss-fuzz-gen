#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/hoextdown/src/buffer.h"  // Correct path for hoedown_buffer related declarations
#include "/src/hoextdown/src/autolink.c"  // Correct path for hoedown_autolink__email_14 implementation

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    size_t rewind = 0;
    hoedown_buffer *buffer = hoedown_buffer_new(64);  // Assume hoedown_buffer_new is provided by the library
    if (!buffer) {
        return 0;  // Handle buffer allocation failure
    }

    uint8_t *data_copy = (uint8_t *)malloc(size);
    if (!data_copy) {
        hoedown_buffer_free(buffer);
        return 0;  // Handle memory allocation failure
    }
    memcpy(data_copy, data, size);

    size_t offset = 0;
    unsigned int flags = 0;

    // Ensure that the offset is within the bounds of the data
    if (offset < size) {
        hoedown_autolink__email(&rewind, buffer, data_copy, offset, size, flags);
    }

    hoedown_buffer_free(buffer);  // Assume hoedown_buffer_free is provided by the library
    free(data_copy);

    return 0;
}