#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/hoextdown/src/buffer.h"

// Function signature for the function-under-test
// Adjusted to match the declaration in buffer.h
void hoedown_buffer_printf(hoedown_buffer *, const char *, ...);

extern int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Initialize a hoedown_buffer
    hoedown_buffer *buffer = hoedown_buffer_new(size > 0 ? size : 1);

    // Ensure the data is null-terminated to be used as a format string
    char *format_string = (char *)malloc(size + 1);
    if (format_string == NULL) {
        hoedown_buffer_free(buffer);
        return 0;
    }
    memcpy(format_string, data, size);
    format_string[size] = '\0';

    // Call the function-under-test
    hoedown_buffer_printf(buffer, format_string);

    // Clean up
    free(format_string);
    hoedown_buffer_free(buffer);

    return 0;
}