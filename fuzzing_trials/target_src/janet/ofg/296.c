#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_296(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Create a Janet object from the input data
    Janet janet_obj;
    if (size >= sizeof(Janet)) {
        // Copy data into a Janet object if size is sufficient
        memcpy(&janet_obj, data, sizeof(Janet));
    } else {
        // If not enough data, just use a default Janet object
        janet_obj = janet_wrap_nil();
    }

    // Call the function-under-test
    JanetBuffer *buffer = janet_unwrap_buffer(janet_obj);

    // Perform any cleanup if necessary
    // Note: Janet does not require explicit cleanup for buffers

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}