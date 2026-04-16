#include <stdint.h>
#include <stddef.h>
#include "/src/hoextdown/src/buffer.h"

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    hoedown_buffer buffer;
    buffer.data = (uint8_t *)data;  // Cast to match the expected type
    buffer.size = size;
    buffer.asize = size;
    buffer.unit = 1;

    // Call the function-under-test
    int result = hoedown_buffer_eq(&buffer, data, size);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result) {
        // Do something if equal
    } else {
        // Do something if not equal
    }

    return 0;
}