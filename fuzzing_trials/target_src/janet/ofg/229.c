#include <stdint.h>
#include <stddef.h>
#include <string.h> // For memcpy
#include <janet.h>  // Ensure this is the correct header for Janet functions

int LLVMFuzzerTestOneInput_229(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize a Janet variable from the input data
    Janet janet_val;
    memcpy(&janet_val, data, sizeof(Janet));

    // Use the remaining data for the integer index
    int32_t index = 0;
    if (size > sizeof(Janet)) {
        index = (int32_t)(data[sizeof(Janet)]); // Use one byte for index
    }

    // Call the function-under-test
    int32_t result = janet_getinteger(&janet_val, index);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}