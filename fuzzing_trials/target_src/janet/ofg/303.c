#include <stdint.h>
#include <string.h>  // Include for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_303(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Ensure that the data is large enough to create a Janet value
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create a Janet value from the input data
    Janet input;
    memcpy(&input, data, sizeof(Janet));

    // Call the function-under-test
    int result = janet_unwrap_boolean(input);

    // Clean up Janet
    janet_deinit();

    return 0;
}