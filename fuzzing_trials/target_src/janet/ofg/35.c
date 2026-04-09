#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Create a Janet object from the input data
    Janet janet_input;
    
    // Ensure the input data is not null and has a size
    if (size > 0) {
        // Create a buffer from the input data
        JanetBuffer *buffer = janet_buffer(size);
        janet_buffer_push_bytes(buffer, data, size);
        
        // Convert buffer to a Janet string
        janet_input = janet_wrap_string(janet_string(buffer->data, buffer->count));
        
        // Call the function-under-test
        JanetString result = janet_to_string(janet_input);
        
        // Use the result to prevent optimization out
        (void)result;

        // Clean up
        janet_buffer_deinit(buffer);
    }

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}