#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"  // Ensure this header is included if it defines JanetArray

// Remove the custom JanetArray definition since it's already defined in janet.h
// and causing a redefinition error

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_364(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t) * 2) {
        return 0; // Not enough data to extract two int32_t values
    }

    // Extract the int32_t values from the input data
    int32_t min_capacity = *((int32_t *)data);
    int32_t growth_factor = *((int32_t *)(data + sizeof(int32_t)));

    // Initialize a JanetArray
    JanetArray array;
    array.count = 0;
    array.capacity = 0;
    array.data = NULL;

    // Call the function-under-test
    janet_array_ensure(&array, min_capacity, growth_factor);

    // Clean up if necessary (e.g., free allocated memory)
    free(array.data);

    return 0;
}

#ifdef __cplusplus
}
#endif