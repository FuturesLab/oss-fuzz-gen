#include <janet.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure the input size is sufficient to create a Janet object
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_obj;
    memcpy(&janet_obj, data, sizeof(Janet));

    // Call the function-under-test
    JanetKeyword result = janet_unwrap_keyword(janet_obj);

    // Clean up the Janet environment
    janet_deinit();

    return 0;
}