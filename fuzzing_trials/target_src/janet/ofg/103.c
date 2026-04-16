#include <stdint.h>
#include <janet.h>

// The function-under-test
Janet janet_lengthv(Janet);

// Fuzzing harness
int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure there is data to process
    if (size == 0) {
        return 0;
    }

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

    // Clean up the Janet environment
    janet_deinit();

    return 0;
}