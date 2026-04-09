#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>   // Include for malloc and free
#include <string.h>   // Include for memcpy
#include "janet.h"    // Ensure this is the correct library for Janet

int LLVMFuzzerTestOneInput_1362(const uint8_t *data, size_t size) {
    // Ensure the size is a multiple of the size of Janet, otherwise return early
    if (size % sizeof(Janet) != 0) {
        return 0;
    }

    // Calculate the number of Janet elements
    size_t num_elements = size / sizeof(Janet);

    // Allocate memory for Janet array
    Janet *janet_array = (Janet *)malloc(num_elements * sizeof(Janet));
    if (janet_array == NULL) {
        return 0;
    }

    // Copy data into Janet array
    memcpy(janet_array, data, size);

    // Initialize the Janet environment
    janet_init();

    // Call the function-under-test
    JanetTuple result = janet_tuple_n(janet_array, num_elements);

    // Check if the result is valid
    if (result == NULL) {
        janet_deinit();
        free(janet_array);
        return 0;
    }

    // Use the result in some meaningful way
    // For example, print the tuple or perform other operations
    // (This is just a placeholder, actual usage depends on the context)
    // printf("Tuple created with %zu elements\n", num_elements);

    // Clean up
    janet_deinit();
    free(janet_array);

    return 0;
}