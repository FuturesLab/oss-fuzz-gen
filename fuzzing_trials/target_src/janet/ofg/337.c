#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_337(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Create a Janet array from the input data
    JanetArray *array = janet_array(size);
    for (size_t i = 0; i < size; i++) {
        array->data[i] = janet_wrap_integer(data[i]);
    }
    array->count = size;

    // Create a Janet key for accessing the array
    Janet key = janet_wrap_integer(0);

    // Call the function-under-test
    Janet result = janet_get(janet_wrap_array(array), key);

    // Clean up
    janet_deinit();

    return 0;
}