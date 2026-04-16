#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"  // Assuming this header file contains the definition for JanetArray

int LLVMFuzzerTestOneInput_365(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for our needs
    if (size < sizeof(int32_t) * 2) {
        return 0;
    }

    // Initialize JanetArray
    JanetArray array;
    array.capacity = 0;
    array.count = 0;
    array.data = NULL;

    // Extract values for count and capacity from the input data
    int32_t count = *(const int32_t *)data;
    int32_t capacity = *(const int32_t *)(data + sizeof(int32_t));

    // Call the function-under-test
    janet_array_ensure(&array, count, capacity);

    // Cleanup if necessary (depends on how JanetArray is defined and used)
    free(array.data);

    return 0;
}