#include <stdint.h>
#include <string.h>  // For memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_301(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a Janet structure
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Create a Janet value from the input data
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Call the function-under-test
    JanetTable *result = janet_unwrap_table(janet_value);

    // Use the result in some way to prevent optimization out
    if (result != NULL) {
        // Access some property of the JanetTable to ensure it's used
        (void)result->count;
    }

    return 0;
}