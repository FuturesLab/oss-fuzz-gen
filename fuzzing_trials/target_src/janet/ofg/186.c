#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Create a Janet array to hold the input data
    Janet *janet_array = (Janet *)data;

    // Define default string (non-NULL)
    const uint8_t *default_string = (const uint8_t *)"default";

    // Set index and count within bounds
    int32_t index = 0;
    int32_t count = (int32_t)(size / sizeof(Janet));

    // Call the function-under-test
    JanetString result = janet_optstring(janet_array, index, count, default_string);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}