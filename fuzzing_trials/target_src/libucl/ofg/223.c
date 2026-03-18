#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    // Ensure the size is at least the size of ucl_object_t
    if (size < sizeof(ucl_object_t)) {
        return 0;
    }

    // Create a ucl_object_t from the data
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj == NULL) {
        return 0;
    }

    // Initialize the ucl_object_t with the provided data
    memcpy(obj, data, sizeof(ucl_object_t));

    // Create a double variable to store the result
    double result = 0.0;

    // Call the function-under-test
    bool success = ucl_object_todouble_safe(obj, &result);

    // Clean up
    free(obj);

    return 0;
}