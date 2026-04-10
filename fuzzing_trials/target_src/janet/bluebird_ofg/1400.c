#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1400(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0;
    }

    // Initialize Janet
    janet_init();

    // Create a Janet array to use as input
    JanetArray *array = janet_array(10);
    for (int i = 0; i < 10 && i < size / sizeof(Janet); i++) {
        Janet value = janet_wrap_integer(data[i]);
        janet_array_push(array, value);
    }

    // Wrap the array in a Janet type
    Janet array_janet = janet_wrap_array(array);

    // Extract an int32_t from the data
    int32_t index = *((int32_t *)(data + size - sizeof(int32_t)));

    // Ensure the index is within bounds
    if (index < 0 || index >= array->count) {
        // Clean up
        janet_deinit();
        return 0;
    }

    // Call the function-under-test
    Janet result = janet_get(array_janet, janet_wrap_integer(index));

    // Clean up
    janet_deinit();

    return 0;
}