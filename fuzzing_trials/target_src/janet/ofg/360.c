#include <janet.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_360(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Ensure the size is sufficient to create a Janet object
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_obj;
    memcpy(&janet_obj, data, sizeof(Janet));

    // Check if the Janet object is a function before unwrapping
    if (janet_checktype(janet_obj, JANET_FUNCTION)) {
        // Call the function under test
        JanetFunction *result = janet_unwrap_function(janet_obj);
        // Use the result in some way if necessary
    }

    // Cleanup Janet runtime
    janet_deinit();

    return 0;
}