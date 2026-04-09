#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Define the fuzzing function
int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Ensure that the size is at least the size of a Janet value
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Cast the input data to a Janet type
    Janet janet_value = *(const Janet *)data;

    // Call the function-under-test
    JanetIntType result = janet_is_int(janet_value);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}