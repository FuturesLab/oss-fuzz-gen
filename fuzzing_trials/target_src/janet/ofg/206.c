#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_206(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the parameters
    if (size < sizeof(Janet) * 2 + sizeof(int32_t) * 2) {
        return 0;
    }

    // Initialize Janet library
    janet_init();

    // Create Janet values from the data
    const Janet *janet_values = (const Janet *)data;
    int32_t n = (int32_t)size / sizeof(Janet); // Number of Janet elements
    int32_t offset = (int32_t)data[size - sizeof(int32_t) * 2];
    int32_t length = (int32_t)data[size - sizeof(int32_t)];

    // Default value
    const Janet *def = janet_values + 1; // Use the second Janet value as default

    // Call the function-under-test
    JanetTuple result = janet_opttuple(janet_values, n, offset, def);

    // Clean up Janet library
    janet_deinit();

    return 0;
}