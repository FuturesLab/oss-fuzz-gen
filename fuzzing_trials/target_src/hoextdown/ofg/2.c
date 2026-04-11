#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/hoextdown/src/buffer.h"

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for use as a string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize a hoedown_buffer
    hoedown_buffer *buf = hoedown_buffer_new(64);
    if (buf == NULL) {
        free(null_terminated_data);
        return 0; // Exit if buffer allocation fails
    }

    // Call the function-under-test
    hoedown_buffer_puts(buf, null_terminated_data);

    // Clean up
    hoedown_buffer_free(buf);
    free(null_terminated_data);

    return 0;
}