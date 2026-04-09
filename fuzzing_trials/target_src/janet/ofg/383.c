#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_383(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet runtime
    janet_init();

    // Allocate memory for Janet array
    Janet *janet_array = (Janet *)data;

    // Define integer parameters
    int32_t n = 0; // Assuming n can be 0 for the starting index
    int32_t def = 0; // Default value
    int32_t cap = 10; // Capacity for the buffer, assuming a small non-zero value

    // Call the function-under-test
    JanetBuffer *buffer = janet_optbuffer(janet_array, n, def, cap);

    // Clean up
    if (buffer != NULL) {
        janet_buffer_deinit(buffer);
    }

    // Deinitialize Janet runtime
    janet_deinit();

    return 0;
}