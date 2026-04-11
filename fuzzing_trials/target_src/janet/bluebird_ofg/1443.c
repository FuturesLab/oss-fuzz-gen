#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1443(const uint8_t *data, size_t size) {
    Janet janet_value;

    // Ensure that the input size is at least the size of a Janet value
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Copy data into a Janet value
    memcpy(&janet_value, data, sizeof(Janet));

    // Call the function-under-test
    int result = janet_checkuint16(janet_value);

    // Use the result in some way to prevent compiler optimizations from removing the call
    (void)result;

    return 0;
}