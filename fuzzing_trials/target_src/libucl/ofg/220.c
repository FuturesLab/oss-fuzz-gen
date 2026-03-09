#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_220(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    // Create a dummy ucl_object_t for testing
    ucl_object_t *obj = ucl_object_new();
    if (obj == NULL) {
        return 0;
    }

    // Feed the input data into the ucl_object
    ucl_object_fromstring_common((const char *)data, size, 0);

    // Initialize a double variable
    double result = 0.0;

    // Call the function-under-test
    bool success = ucl_object_todouble_safe(obj, &result);

    // Clean up
    ucl_object_unref(obj);

    return 0;
}