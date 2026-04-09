#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_263(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Create a JanetArray with some elements based on input data
    JanetArray *array = janet_array(size);
    for (size_t i = 0; i < size; i++) {
        // Fill the array with values from the input data
        array->data[i] = janet_wrap_integer(data[i]);
    }
    array->count = size;

    // Call the function-under-test
    if (array->count > 0) {
        Janet result = janet_array_pop(array);
        // Optionally, use the result to affect control flow or logic
        if (janet_checktype(result, JANET_NUMBER)) {
            double num = janet_unwrap_number(result);
            // Use num in some way to ensure it's not optimized away
            if (num < 0) {
                janet_array_push(array, janet_wrap_number(-num));
            }
        }
    }

    // Cleanup Janet runtime
    janet_deinit();

    return 0;
}