#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <janet.h>

// Function-under-test
void *janet_getpointer(const Janet *array, int32_t index);

int LLVMFuzzerTestOneInput_242(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0; // Not enough data to form a valid input
    }

    // Ensure we have enough data to form a Janet array and an index
    size_t janet_array_size = (size - sizeof(int32_t)) / sizeof(Janet);
    Janet *janet_array = (Janet *)malloc(janet_array_size * sizeof(Janet));
    if (janet_array == NULL) {
        return 0; // Memory allocation failed
    }

    // Copy data into the Janet array
    for (size_t i = 0; i < janet_array_size; ++i) {
        janet_array[i] = ((Janet *)data)[i];
    }

    // Extract an int32_t index from the remaining data
    int32_t index = *((int32_t *)(data + janet_array_size * sizeof(Janet)));

    // Ensure the index is within bounds
    if (index < 0 || index >= janet_array_size) {
        free(janet_array);
        return 0; // Index out of bounds
    }

    // Call the function-under-test
    void *result = janet_getpointer(janet_array, index);

    // Clean up
    free(janet_array);

    return 0;
}