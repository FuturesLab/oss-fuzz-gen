#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_295(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Ensure that the size is sufficient to create a Janet object
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create a Janet object from the input data
    // Janet is a tagged union, so we'll interpret the data as a Janet value
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Call the function-under-test
    JanetBuffer *buffer = janet_unwrap_buffer(janet_value);

    // Perform any additional operations on the buffer if necessary
    // For fuzzing purposes, we just check if the buffer is not NULL
    if (buffer != NULL) {
        // Optionally, perform operations on buffer to ensure it is valid
        // For example, access buffer->data or buffer->count
    }

    // Clean up Janet runtime
    janet_deinit();

    return 0;
}