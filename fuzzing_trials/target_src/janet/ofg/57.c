#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include this for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    if (size < sizeof(int64_t)) {
        return 0; // Not enough data to form an int64_t
    }

    // Create a Janet object from the input data
    int64_t value;
    memcpy(&value, data, sizeof(int64_t));

    Janet janet_value = janet_wrap_integer(value);

    // Call the function-under-test
    int64_t result = janet_unwrap_s64(janet_value);

    // Use the result in some way to prevent the compiler from optimizing it away
    (void)result;

    return 0;
}