#include <stdint.h>
#include <stddef.h>
#include <janet.h>

extern double janet_getnumber(const Janet *array, int32_t index);

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Ensure the size is at least large enough to create a Janet array with one element
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Create a Janet array from the input data
    Janet janetArray[1];
    janetArray[0] = janet_wrap_number((double)data[0]);

    // Define an index to access the Janet array
    int32_t index = 0;

    // Call the function-under-test
    double result = janet_getnumber(janetArray, index);

    // Use the result to prevent compiler optimizations from removing the call
    if (result == 0.0) {
        // Do nothing, just a placeholder
    }

    return 0;
}