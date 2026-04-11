#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "/src/hoextdown/src/buffer.h" // Ensure this header includes the definition for hoedown_buffer

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Check if the input data size is zero
    if (size == 0) {
        return 0;
    }

    // Initialize a hoedown_buffer
    hoedown_buffer *buffer = hoedown_buffer_new(size);
    if (buffer == NULL) {
        return 0;
    }

    // Append data to the hoedown_buffer
    hoedown_buffer_put(buffer, data, size);

    // Create a temporary file
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        hoedown_buffer_free(buffer);
        return 0;
    }

    // Call the function-under-test
    // Ensure the buffer has content before calling hoedown_buffer_putf
    if (buffer->size > 0) {
        hoedown_buffer_putf(buffer, temp_file);
    }

    // Clean up
    fclose(temp_file);
    hoedown_buffer_free(buffer);

    return 0;
}