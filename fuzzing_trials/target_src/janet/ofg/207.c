#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Fuzzer entry point
int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a Janet object
    if (size < sizeof(double)) {
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_value = janet_wrap_number(*((double *)data));

    // Call the function-under-test
    int result = janet_checktype(janet_value, JANET_NUMBER);

    // Use the result in some way to prevent the compiler from optimizing it out
    (void)result;

    return 0;
}