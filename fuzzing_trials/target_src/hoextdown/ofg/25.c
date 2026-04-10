#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/hoextdown/src/buffer.h"

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure there is input data to work with
    if (size == 0) {
        return 0; // No data to process
    }

    // Initialize hoedown_buffer
    hoedown_buffer buffer;
    buffer.data = (uint8_t *)malloc(size);
    if (buffer.data == NULL) {
        return 0; // Allocation failed, exit
    }
    buffer.size = size;
    buffer.asize = size;
    buffer.unit = 1;

    // Copy the input data into the buffer
    memcpy(buffer.data, data, size);

    // Call the function-under-test with meaningful input
    // Assuming hoedown_buffer_eq checks if the buffer content equals the input data
    int result = hoedown_buffer_eq(&buffer, data, size);

    // Use the result in some way to ensure the function is being tested
    if (result) {
        // Do something if the buffer and data are equal
        // This is just to ensure the function is invoked meaningfully
    }

    // Clean up
    free(buffer.data);

    return 0;
}