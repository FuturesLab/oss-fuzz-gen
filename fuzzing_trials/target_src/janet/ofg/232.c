#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Create a JanetArray with some initial capacity
    JanetArray *array = janet_array(10);

    // Fill the array with some data from the input
    for (size_t i = 0; i < size && i < 10; i++) {
        // Convert each byte of data into a Janet integer
        Janet value = janet_wrap_integer(data[i]);
        // Push the value into the array
        janet_array_push(array, value);
    }

    // Call the function-under-test
    Janet result = janet_wrap_array(array);

    // Use the result in some way to avoid compiler optimizations removing it
    (void)result;

    // Clean up the Janet environment
    janet_deinit();

    return 0;
}