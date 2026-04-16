#include <janet.h>
#include <string.h> // For memcpy
#include <stddef.h> // For size_t

int LLVMFuzzerTestOneInput_359(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a Janet object
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Call the function-under-test
    JanetFunction *result = janet_unwrap_function(janet_value);

    // Optional: Use the result in some way to prevent compiler optimizations
    if (result != NULL) {
        // Do something with the result, e.g., access its fields
        (void)result->def;
    }

    return 0;
}