#include "janet.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_1203(const uint8_t *data, size_t size) {
    // Initialize the Janet runtime
    janet_init();

    // Check if the input size is sufficient for a double
    if (size < sizeof(double)) {
        janet_deinit();
        return 0;
    }

    // Initialize a Janet value from the input data
    double input_number = *(double *)data;
    Janet janet_value = janet_wrap_number(input_number);

    // Create a new environment for the function
    JanetTable *env = janet_table(0); // Corrected line to create a new table

    // Call the function-under-test
    JanetFunction *result = janet_thunk_delay(janet_value);

    // Use the result to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // Do something with the result, e.g., calling a function
        janet_gcroot(janet_wrap_function(result));
        janet_gcunroot(janet_wrap_function(result));
    }

    // Clean up the Janet runtime
    janet_deinit();

    return 0;
}