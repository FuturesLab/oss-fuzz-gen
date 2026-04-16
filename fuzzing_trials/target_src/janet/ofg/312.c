#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include <janet.h> // Assuming the Janet library provides this header

// Remove the 'extern "C"' as this is C code, not C++
int LLVMFuzzerTestOneInput_312(const uint8_t *data, size_t size) {
    // Initialize Janet environment
    janet_init();

    // Create a JanetArray
    JanetArray *array = janet_array(10); // Initial size of 10

    // Ensure the size is sufficient to create a Janet object
    if (size >= sizeof(Janet)) {
        // Create a Janet object from the input data
        Janet janet_value;
        memcpy(&janet_value, data, sizeof(Janet));

        // Call the function-under-test
        janet_array_push(array, janet_value);
    }

    // Clean up Janet environment
    janet_deinit();

    return 0;
}