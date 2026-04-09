#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// The extern declaration is unnecessary because janet_wrap_integer is a macro
// extern Janet janet_wrap_integer(int32_t x);

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t)) {
        return 0;
    }

    int32_t input;
    // Copy the first 4 bytes from data to input
    input = *(int32_t *)data;

    // Call the function-under-test
    Janet result = janet_wrap_integer(input);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}