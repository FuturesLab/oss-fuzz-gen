#include <stdint.h>
#include <janet.h>
#include <stdio.h>
#include <string.h>  // Include string.h for memcpy

int LLVMFuzzerTestOneInput_272(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet
    janet_init();

    // Create a Janet object from the input data
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Call the function-under-test
    JanetType type = janet_type(janet_value);

    // Optionally, print the type for debugging purposes
    printf("JanetType: %d\n", type);

    // Clean up Janet
    janet_deinit();

    return 0;
}