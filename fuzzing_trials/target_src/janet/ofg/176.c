#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    // Ensure there's enough data for an integer index
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Interpret the first 4 bytes of data as an integer index
    int32_t index = *(const int32_t *)data;

    // Calculate the number of Janet objects we can create from the remaining data
    size_t num_janets = (size - sizeof(int32_t)) / sizeof(Janet);

    // Allocate an array of Janet objects
    Janet *janet_array = (Janet *)malloc(num_janets * sizeof(Janet));
    if (!janet_array) {
        return 0;
    }

    // Initialize the Janet objects with the remaining data
    for (size_t i = 0; i < num_janets; i++) {
        janet_array[i] = janet_wrap_integer((int32_t)data[sizeof(int32_t) + i]);
    }

    // Ensure the index is within bounds
    if (index >= 0 && (size_t)index < num_janets) {
        // Call the function-under-test
        int result = janet_getboolean(janet_array, index);
    }

    // Clean up
    free(janet_array);

    return 0;
}