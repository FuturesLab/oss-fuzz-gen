#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_310(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract two int32_t values
    if (size < sizeof(int32_t) * 2) {
        return 0;
    }

    // Initialize Janet
    janet_init();

    // Create a JanetBuffer
    JanetBuffer *buffer = janet_buffer(10); // Initializing with some arbitrary size

    // Extract two int32_t values from the input data
    int32_t size_hint = *((int32_t *)data);
    int32_t growth_factor = *((int32_t *)(data + sizeof(int32_t)));

    // Ensure size_hint and growth_factor are within a reasonable range
    // to avoid excessive memory allocation or undefined behavior
    size_hint = size_hint < 0 ? -size_hint : size_hint;
    growth_factor = growth_factor < 0 ? -growth_factor : growth_factor;

    // Add a check to ensure size_hint and growth_factor are not zero
    // This ensures the function under test is meaningfully invoked
    if (size_hint == 0) size_hint = 1;
    if (growth_factor == 0) growth_factor = 1;

    // Call the function-under-test
    janet_buffer_ensure(buffer, size_hint, growth_factor);

    // Use the buffer to ensure it's not null and perform some operations
    // This helps to exercise the buffer and potentially reveal issues
    for (int i = 0; i < size_hint && i < size; i++) {
        janet_buffer_push_u8(buffer, (uint8_t)(data[i]));
    }

    // Clean up
    janet_deinit();

    return 0;
}