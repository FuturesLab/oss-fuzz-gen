#include <stdint.h>
#include <stddef.h>
#include <janet.h>
#include <string.h>
#include <stdlib.h>

// Function prototype for janet_getstruct
JanetStruct janet_getstruct(const Janet *janet_array, int32_t index);

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a Janet array and an index
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0;
    }

    // Calculate the number of Janet elements we can fit in the data
    size_t janet_array_size = (size - sizeof(int32_t)) / sizeof(Janet);
    if (janet_array_size == 0) {
        return 0;
    }

    // Initialize a Janet array with the data
    Janet *janet_array = (Janet *)malloc(janet_array_size * sizeof(Janet));
    if (!janet_array) {
        return 0;
    }
    memcpy(janet_array, data, janet_array_size * sizeof(Janet));

    // Extract an index from the data
    int32_t index = *((int32_t *)(data + janet_array_size * sizeof(Janet)));

    // Ensure the index is within bounds
    if (index < 0 || index >= janet_array_size) {
        free(janet_array);
        return 0;
    }

    // Call the function-under-test
    JanetStruct result = janet_getstruct(janet_array, index);

    // Clean up
    free(janet_array);

    // Return 0 to indicate success
    return 0;
}