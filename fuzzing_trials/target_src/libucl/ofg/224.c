#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h> // Include this for the bool type

int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    // Initialize a ucl_object_t object
    ucl_object_t obj;
    obj.type = UCL_FLOAT; // Set type to float for testing
    obj.value.dv = *(double *)data; // Use the input data as the double value

    double result;
    bool success = ucl_object_todouble_safe(&obj, &result);

    // Ensure the function is called
    (void)success;

    return 0;
}