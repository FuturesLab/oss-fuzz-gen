#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Fuzzing harness for janet_buffer_push_u16
int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract a uint16_t value
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Initialize a JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10); // Initializing with a capacity of 10

    // Extract a uint16_t value from the input data
    uint16_t value = *((const uint16_t *)data);

    // Call the function-under-test
    janet_buffer_push_u16(&buffer, value);

    // Clean up the JanetBuffer
    janet_buffer_deinit(&buffer);

    return 0;
}