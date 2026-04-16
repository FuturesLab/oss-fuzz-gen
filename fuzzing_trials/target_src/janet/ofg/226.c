#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// The janet_unwrap_integer is a macro, no need to declare it as an extern function

int LLVMFuzzerTestOneInput_226(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Construct a Janet value from the input data
    Janet janet_value;
    int32_t integer_value = *((int32_t *)data);
    janet_value = janet_wrap_integer(integer_value);

    // Call the function-under-test
    int32_t result = janet_unwrap_integer(janet_value);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}