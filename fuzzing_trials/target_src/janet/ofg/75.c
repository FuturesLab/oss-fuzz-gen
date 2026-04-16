#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// The macro 'janet_wrap_integer' is defined in janet.h and expands to a function call.
// We don't need to declare it as an extern function.

int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t)) {
        return 0;
    }

    int32_t input_value;
    // Copy the first 4 bytes from data into input_value
    input_value = *(const int32_t *)data;

    // Call the function-under-test
    Janet result = janet_wrap_integer(input_value);

    // Use the result in some way to prevent compiler optimizations from removing the call
    (void)result;

    return 0;
}