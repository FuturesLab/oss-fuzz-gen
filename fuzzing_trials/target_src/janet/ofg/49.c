#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include this for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize a Janet variable from the input data
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Call the function-under-test
    int result = janet_checkuint(janet_value);

    // Use the result to avoid compiler optimizations
    (void)result;

    return 0;
}