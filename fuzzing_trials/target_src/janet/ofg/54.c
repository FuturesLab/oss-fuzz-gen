#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Create a JanetArray with some initial elements
    JanetArray *array = janet_array(10);
    for (size_t i = 0; i < 10 && i < size; i++) {
        // Add elements to the array using the input data
        janet_array_push(array, janet_wrap_integer(data[i]));
    }

    // Call the function-under-test
    Janet result = janet_array_peek(array);

    // Use the result in some way (for demonstration purposes, we'll just print it)
    janet_printf("Peeked value: %v\n", result);

    // Clean up the Janet environment
    janet_deinit();

    return 0;
}