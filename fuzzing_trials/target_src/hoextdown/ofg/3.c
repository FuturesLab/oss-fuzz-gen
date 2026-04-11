#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/hoextdown/src/buffer.h"  // Correct header file for hoedown_buffer

// Function-under-test
void hoedown_buffer_puts(hoedown_buffer *buffer, const char *str);

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Initialize a hoedown_buffer
    hoedown_buffer *buffer = hoedown_buffer_new(64); // Assuming an initial size of 64

    // Ensure the data is null-terminated
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        hoedown_buffer_free(buffer);
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    hoedown_buffer_puts(buffer, null_terminated_data);

    // Clean up
    free(null_terminated_data);
    hoedown_buffer_free(buffer);

    return 0;
}