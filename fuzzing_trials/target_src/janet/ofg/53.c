#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Fuzzing harness for janet_array_peek function
int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Create a JanetArray with some initial capacity
    int32_t initial_capacity = 10;
    JanetArray *array = janet_array(initial_capacity);

    // Populate the array with some dummy Janet values
    for (int32_t i = 0; i < initial_capacity && i < size; i++) {
        Janet value = janet_wrap_integer((int32_t)data[i]);
        janet_array_push(array, value);
    }

    // Call the function-under-test
    Janet result = janet_array_peek(array);

    // Clean up Janet runtime
    janet_deinit();

    // Return 0 to indicate successful execution
    return 0;
}