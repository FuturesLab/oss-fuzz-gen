#include <janet.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Ensure the input data is not empty
    if (size == 0) {
        janet_deinit();
        return 0;
    }

    // Create a Janet buffer from the input data
    JanetBuffer *buffer = janet_buffer(size);
    janet_buffer_push_bytes(buffer, data, size);

    // Convert the buffer to a Janet string
    Janet janetValue = janet_wrap_buffer(buffer);
    JanetString janetString = janet_to_string(janetValue);

    // Use the Janet string (e.g., print it or perform some operations)
    // For fuzzing, we just ensure the function is called
    (void)janetString;

    // Clean up
    janet_deinit();

    return 0;
}