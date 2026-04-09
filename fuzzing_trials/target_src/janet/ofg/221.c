#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// The janet_wrap_boolean is a macro, so we don't need an extern declaration for it.

int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    // Convert the input data to an integer
    int input_value = *((int *)data);

    // Call the function-under-test using the macro directly
    Janet result = janet_wrap_boolean(input_value);

    // Use the result to avoid compiler warnings about unused variables
    (void)result;

    return 0;
}