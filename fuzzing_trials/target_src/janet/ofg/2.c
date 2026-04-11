#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    JanetBuffer buffer;
    uint32_t value;

    // Initialize the JanetBuffer
    janet_buffer_init(&buffer, 10);

    // Ensure there's enough data to extract a uint32_t value
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Extract a uint32_t value from the input data
    value = *(const uint32_t *)data;

    // Call the function-under-test
    janet_buffer_push_u32(&buffer, value);

    // Clean up and return
    janet_buffer_deinit(&buffer);
    return 0;
}