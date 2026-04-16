#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract an int32_t index
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Create a Janet array from the input data
    Janet *janet_array = (Janet *)janet_malloc(size * sizeof(Janet));
    if (janet_array == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        janet_array[i] = janet_wrap_integer(data[i]);
    }

    // Extract an int32_t index from the data
    int32_t index = *((int32_t *)(data + size - sizeof(int32_t)));

    // Ensure the index is within bounds
    if (index < 0 || index >= size) {
        janet_free(janet_array);
        return 0;
    }

    // Call the function-under-test
    JanetCFunction func = janet_getcfunction(janet_array, index);

    // Ensure the function is valid before calling it
    if (func != NULL) {
        Janet result;
        Janet *args = NULL; // Assuming the function does not require arguments
        int32_t argc = 0;   // Number of arguments
        result = func(argc, args);
    }

    // Clean up
    janet_free(janet_array);

    return 0;
}