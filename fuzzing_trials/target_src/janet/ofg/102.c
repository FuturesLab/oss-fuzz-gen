#include <stdint.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Create a Janet array from the input data
    JanetArray *array = janet_array(size);
    for (size_t i = 0; i < size; i++) {
        array->data[i] = janet_wrap_integer(data[i]);
    }
    array->count = size;

    // Wrap the array in a Janet value
    Janet wrapped_array = janet_wrap_array(array);

    // Call the function-under-test
    Janet result = janet_lengthv(wrapped_array);

    // Clean up Janet
    janet_deinit();

    return 0;
}