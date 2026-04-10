#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_392(const uint8_t *data, size_t size) {
    if (size < sizeof(int) * 2) {
        return 0;
    }

    // Initialize Janet
    janet_init();

    // Create a JanetBuffer
    JanetBuffer *buffer = janet_buffer(10);

    // Extract two integers from the data
    int indent = *((int *)data);
    int width = *(((int *)data) + 1);

    // Create a Janet value from the remaining data
    Janet value;
    if (size > sizeof(int) * 2) {
        value = janet_wrap_string(janet_string(data + sizeof(int) * 2, size - sizeof(int) * 2));
    } else {
        value = janet_wrap_nil();
    }

    // Call the function-under-test
    JanetBuffer *result = janet_pretty(buffer, indent, width, value);

    // Clean up
    janet_deinit();

    return 0;
}