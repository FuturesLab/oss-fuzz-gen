#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_356(const uint8_t *data, size_t size) {
    // Declare and initialize a JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, size);

    // Fill the buffer with data
    if (size > 0) {
        janet_buffer_push_bytes(&buffer, data, size);
    }

    // Call the function-under-test
    janet_buffer_deinit(&buffer);

    return 0;
}