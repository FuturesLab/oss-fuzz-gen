#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/hoextdown/src/buffer.h"

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for creating a string
    if (size < 2) {
        return 0;
    }

    // Create a hoedown_buffer instance
    hoedown_buffer buffer;
    buffer.data = (uint8_t *)data;
    buffer.size = size;
    buffer.asize = size;
    buffer.unit = 1;

    // Create a null-terminated string from the input data
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        return 0;
    }
    memcpy(str, data, size);
    str[size] = '\0';

    // Call the function-under-test
    hoedown_buffer_eqs(&buffer, str);

    // Clean up
    free(str);

    return 0;
}