#include <stdint.h>
#include <string.h> // Include string.h for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a Janet type
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize a Janet object from the input data
    Janet janet_input;
    memcpy(&janet_input, data, sizeof(Janet));

    // Call the function-under-test
    JanetCFunction result = janet_unwrap_cfunction(janet_input);

    // Use the result in some way to prevent optimizations from removing the call
    if (result != NULL) {
        // Optionally, invoke the function if it's a valid pointer
        result(NULL, 0);
    }

    return 0;
}