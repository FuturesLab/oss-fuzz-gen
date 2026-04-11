#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to extract an int
    }

    // Extract an integer from the input data
    int input_value = *((int *)data);

    // Convert the integer to a boolean value
    int boolean_value = input_value != 0;

    // Call the function-under-test
    Janet result = janet_wrap_boolean(boolean_value);

    // Optionally, perform some operations with the result to ensure it's used
    JanetType type = janet_type(result);
    if (type == JANET_BOOLEAN) {
        // Do something with the boolean result
    }

    return 0;
}