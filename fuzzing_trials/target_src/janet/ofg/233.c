#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_233(const uint8_t *data, size_t size) {
    JanetArray *array;
    Janet wrapped;

    // Initialize the Janet environment
    janet_init();

    // Create a JanetArray with a non-zero size
    array = janet_array(1);

    // Fill the array with some dummy data
    for (size_t i = 0; i < array->capacity && i < size; i++) {
        array->data[i] = janet_wrap_integer((int32_t)data[i]);
    }
    array->count = (int32_t)(array->capacity < size ? array->capacity : size);

    // Call the function-under-test
    wrapped = janet_wrap_array(array);

    // Clean up Janet environment after use
    janet_deinit();

    return 0;
}