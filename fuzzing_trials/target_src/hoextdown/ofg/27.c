#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/hoextdown/src/buffer.h"
#include "/src/hoextdown/src/escape.c"

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize a hoedown_buffer
    hoedown_buffer *buf = hoedown_buffer_new(size);

    // Use a non-zero flag value for the int parameter
    int flag = 1;

    // Call the function-under-test
    hoedown_escape_html(buf, data, size, flag);

    // Clean up the buffer
    hoedown_buffer_free(buf);

    return 0;
}