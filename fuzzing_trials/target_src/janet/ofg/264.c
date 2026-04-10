#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_264(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Create a JanetArray
    JanetArray *array = janet_array(10);

    // Populate the array with some data from the fuzz input
    for (size_t i = 0; i < size && i < 10; i++) {
        Janet value = janet_wrap_integer(data[i]);
        janet_array_push(array, value);
    }

    // Call the function-under-test
    Janet popped_value = janet_array_pop(array);

    // Use the popped value to prevent compiler optimization
    (void)popped_value;

    // Clean up Janet
    janet_deinit();

    return 0;
}