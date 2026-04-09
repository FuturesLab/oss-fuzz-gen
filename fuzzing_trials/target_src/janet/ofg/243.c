#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_243(const uint8_t *data, size_t size) {
    // Ensure that there is enough data to extract an index
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Create a Janet array to use as a test input
    JanetArray *array = janet_array(10);
    for (int i = 0; i < 10; i++) {
        array->data[i] = janet_wrap_integer(i);
    }
    array->count = 10;

    // Extract an index from the input data
    int32_t index = *(int32_t *)data;

    // Wrap the array in a Janet type
    Janet wrapped_array = janet_wrap_array(array);

    // Call the function-under-test
    Janet result = janet_getindex(wrapped_array, index);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}