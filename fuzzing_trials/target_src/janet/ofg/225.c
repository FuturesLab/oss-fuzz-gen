#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a Janet integer
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Create a Janet integer from the input data
    int32_t value;
    memcpy(&value, data, sizeof(int32_t));

    // Wrap the integer into a Janet type
    Janet janet_value = janet_wrap_integer(value);

    // Call the function-under-test
    int32_t result = janet_unwrap_integer(janet_value);

    // Use the result to avoid compiler optimizations
    (void)result;

    return 0;
}