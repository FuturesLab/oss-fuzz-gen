#include <stdint.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_307(const uint8_t *data, size_t size) {
    Janet janet_value;
    JanetArray *result;

    // Initialize the Janet environment
    janet_init();

    // Ensure the size is sufficient for creating a Janet array
    if (size >= sizeof(JanetArray)) {
        // Create a Janet array from the input data
        JanetArray *array = janet_array(size / sizeof(Janet));
        for (size_t i = 0; i < array->count; i++) {
            array->data[i] = janet_wrap_integer((int32_t)data[i]);
        }

        // Wrap the array into a Janet type
        janet_value = janet_wrap_array(array);

        // Call the function-under-test
        result = janet_unwrap_array(janet_value);

        // Use the result in some way to avoid compiler optimizations
        if (result != NULL) {
            // Do something with result, e.g., access its fields
            (void)result->count;
        }
    }

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}